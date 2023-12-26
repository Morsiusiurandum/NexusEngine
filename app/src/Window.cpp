#include "Window.h"

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept: hInst(GetModuleHandle(nullptr)) {

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = HandleMsgSetup;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetInstance();
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = CHAR2LPCWSTR(GetName());
    wc.hIconSm = nullptr;
    //register a window
    RegisterClassEx(&wc);
}

Window::WindowClass::~ WindowClass() {
    UnregisterClass(reinterpret_cast<LPCWSTR>(wndClassName), GetInstance());
}

const char *Window::WindowClass::GetName() noexcept {
    return wndClassName;
}


HINSTANCE Window::WindowClass::GetInstance() noexcept {
    return wndClass.hInst;
}


Window::Window(int width, int height, const WCHAR *name) noexcept {
    RECT window_rect;
    window_rect.left = 100;
    window_rect.right = width + window_rect.left;
    window_rect.top = 100;
    window_rect.bottom = height + window_rect.top;
    DWORD window_style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
    AdjustWindowRect(&window_rect, window_style, FALSE);
    

    //creat window and get the instance
    hWnd = CreateWindow(
            CHAR2LPCWSTR(WindowClass::GetName()),
            name,
            window_style, CW_USEDEFAULT, CW_USEDEFAULT,
            window_rect.right - window_rect.left, window_rect.bottom - window_rect.top,
            nullptr, nullptr,
            WindowClass::GetInstance(), this);


    ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window() {
    DestroyWindow(hWnd);
}

LRESULT Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    //weather is in no-client
    if (msg == WM_NCCREATE) {
        const auto *const pCreate = reinterpret_cast<const CREATESTRUCT *const>(lParam);
        auto *const pWnd = static_cast<Window *const>(pCreate->lpCreateParams);

        //store the ptr in user data
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) pWnd);
        //use thunk to deal with messages
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR) &Window::HandleMsgThunk);
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}


LRESULT Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    auto *const pWnd = reinterpret_cast<Window *const>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
