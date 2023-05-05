#include<windows.h>

const wchar_t pClassName[] = L"D3D11";

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //register a window
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = DefWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = pClassName;
    wc.hIconSm = nullptr;
    RegisterClassEx(&wc);

    //create a window instance
    DWORD dwStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
    HWND hWnd = CreateWindowEx(0, pClassName, L"Test Window", dwStyle, 200, 200, 640, 480, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hWnd, SW_SHOW);

    return 0;
}