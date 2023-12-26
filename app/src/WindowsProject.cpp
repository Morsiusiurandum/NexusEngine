#include "Window.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

    Window wnd(800, 300, CHAR2LPCWSTR("WTF?"));
    
    MSG msg;
    BOOL msgResult;
    while ((msgResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msgResult == -1 ? -1 : (int) msg.wParam;
}