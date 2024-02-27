#include "Window.h"

Window::Exception::Exception(const int line, const char *file, const HRESULT hResult) noexcept :
    NexusException(line, file), hResult(hResult) {}

auto Window::Exception::TranslateErrorCode(HRESULT hResult) noexcept -> std::string
{
    char *message_buffer = nullptr;
    // windows will allocate memory for err string and make our pointer point to it

    // 0 string length returned indicates a failure
    if (const DWORD format_message_length = FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                nullptr,
                hResult,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                message_buffer,
                0,
                nullptr);
        format_message_length == 0)
    {
        return "Unidentified error code";
    }
    // copy error string from windows-allocated buffer to std::string
    std::string error_string = message_buffer;
    // free windows buffer
    LocalFree(message_buffer);
    return error_string;
}

auto Window::Exception::what() const noexcept -> const char *
{
    std::ostringstream oss;
    oss << GetType() << std::endl
            << "[Error Code]" << GetErrorCode() << std::endl
            << "[Description]" << GetErrorString() << std::endl;
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

auto Window::Exception::GetType() const noexcept -> const char *
{
    return "Nexus Windows Exception";
}

auto Window::Exception::GetErrorCode() const noexcept -> HRESULT
{
    return hResult;
}

auto Window::Exception::GetErrorString() const noexcept -> std::string
{
    return TranslateErrorCode(hResult);
}

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept :
    hInst(GetModuleHandle(nullptr))
{

    WNDCLASSEX wc    = {0};
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_OWNDC;
    wc.lpfnWndProc   = HandleMsgSetup;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = GetInstance();
    wc.hIcon         = nullptr;
    wc.hCursor       = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName  = nullptr;
    wc.lpszClassName = CHAR2LPCWSTR(GetName());
    wc.hIconSm       = nullptr;
    //register a window
    RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClass(reinterpret_cast<LPCWSTR>(wndClassName), GetInstance());
}

auto Window::WindowClass::GetName() noexcept -> const char *
{
    return wndClassName;
}

auto Window::WindowClass::GetInstance() noexcept -> HINSTANCE
{
    return wndClass.hInst;
}

Window::Window(const int width, const int height, const WCHAR *name) :
    width(width), height(height)
{
    RECT window_rect;
    window_rect.left             = 100;
    window_rect.right            = width + window_rect.left;
    window_rect.top              = 100;
    window_rect.bottom           = height + window_rect.top;
    constexpr DWORD window_style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
    if ((AdjustWindowRect(&window_rect, window_style, FALSE)) == 0)
    {
        throw NEXUS_LAST_EXCEPT();
    }

    //creat window and get the instance
    hWnd = CreateWindow(
            CHAR2LPCWSTR(WindowClass::GetName()),
            name,
            window_style,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            window_rect.right - window_rect.left,
            window_rect.bottom - window_rect.top,
            nullptr,
            nullptr,
            WindowClass::GetInstance(),
            this
            );

    if (hWnd == nullptr)
    {
        throw NEXUS_LAST_EXCEPT();
    }

    ShowWindow(hWnd, SW_SHOWDEFAULT);

    graphics_ptr = std::make_unique<Graphics>(hWnd);

}

Window::~Window()
{
    DestroyWindow(hWnd);
}

auto Window::ProcessMessage() noexcept -> std::optional<int>
{
    MSG msg;
    // while queue has messages, remove and dispatch them (but do not block on empty queue)
    while (PeekMessage(&msg, nullptr, 0, 0,PM_REMOVE))
    {
        // check for quit because peekmessage does not signal this via return val
        if (msg.message == WM_QUIT)
        {
            // return optional wrapping int (arg to PostQuitMessage is in wparam) signals quit
            return static_cast<int>(msg.wParam);
        }

        // TranslateMessage will post auxilliary WM_CHAR messages from key msgs
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // return empty optional when not quitting app
    return {};
}

auto Window::GetGraphics() const -> ::Graphics &
{
    return *graphics_ptr;
}

auto Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{

    //weather is in no-client
    if (msg == WM_NCCREATE)
    {
        const auto *const pCreate = reinterpret_cast<const CREATESTRUCT * const>(lParam);
        auto *const       pWnd    = static_cast<Window * const>(pCreate->lpCreateParams);

        //store the ptr in user data
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        //use thunk to deal with messages
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

auto Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{

    auto *const pWnd = reinterpret_cast<Window * const>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

auto Window::HandleMsg(HWND hWnd, const UINT msg, const WPARAM wParam, LPARAM lParam) -> LRESULT
{
    //Keyboard Messages
    switch (msg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        // Clear state when the main window loses focus
        case WM_KILLFOCUS:
            keyboard.ClearState();
            break;

        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            // To distinguish between a continuous press and a single click
            // MSDN says that the 30th position of the lParam is the discriminating bit
            if (constexpr int bits = 0x40000000; ((lParam & bits) == 0) && !keyboard.AutoRepeatIsEnabled())
            {
                keyboard.OnKeyPressed(wParam);
            }
            break;

        case WM_SYSKEYUP:
        case WM_KEYUP:
            keyboard.OnKeyReleased(wParam);
            break;
        case WM_CHAR:
            keyboard.OnChar(static_cast<char>(wParam));
            break;
        default:
            break;
    }

    //Mouse Messages
    switch (msg)
    {
        case WM_MOUSEMOVE:
        {
            if (const auto [x, y] = MAKEPOINTS(lParam);
                x >= 0 && x < width && y >= 0 && y < height)
            {
                mouse.OnMouseMove(x, y);
                if (!mouse.IsInWindow())
                {
                    SetCapture(hWnd);
                    mouse.OnMouseEnter();
                }
            } else
            {
                if (wParam & (MK_LBUTTON | MK_RBUTTON))
                {
                    mouse.OnMouseMove(x, y);
                } else
                {
                    ReleaseCapture();
                    mouse.OnMouseLeave();
                }
            }

            break;
        }
        case WM_LBUTTONDOWN:
        {
            const auto [x, y] = MAKEPOINTS(lParam);
            mouse.OnLeftPressed(x, y);
            break;
        }
        case WM_RBUTTONDOWN:
        {

            const auto [x, y] = MAKEPOINTS(lParam);
            mouse.OnRightPressed(x, y);
            break;
        }
        case WM_LBUTTONUP:
        {

            const auto [x, y] = MAKEPOINTS(lParam);
            mouse.OnLeftReleased(x, y);
            break;
        }
        case WM_RBUTTONUP:
        {

            const auto [x, y] = MAKEPOINTS(lParam);
            mouse.OnRightReleased(x, y);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            const auto [x, y] = MAKEPOINTS(lParam);
            const int  delta  = GET_WHEEL_DELTA_WPARAM(wParam);
            mouse.OnWheelDelta(x, y, delta);
            break;
        }
        default:
        {
            break;
        }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
