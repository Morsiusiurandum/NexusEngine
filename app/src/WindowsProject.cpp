#include "Window.h"

wchar_t *convertCharArrayToLPCWSTR(const char *charArray);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

    Window wnd(800, 300, convertCharArrayToLPCWSTR("WTF?"));
    
    MSG msg;
    BOOL msgResult;
    while ((msgResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msgResult == -1 ? -1 : (int) msg.wParam;
}

wchar_t *convertCharArrayToLPCWSTR(const char *charArray) {
    auto *wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}