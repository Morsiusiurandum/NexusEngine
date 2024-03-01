#include "App.h"


App::App()
    : window(800, 600, CHAR2LPCWSTR("Start Window")), timer()
{
}

auto App::Awake() -> int
{
    while (true)
    {
        if (const auto e_code = window.ProcessMessage())
        {
            return *e_code;
        }
        Update();
    }
}

auto App::Update() -> void
{

    window.GetGraphics().EndFrame();
    const float r = sin(timer.Peek());
    window.GetGraphics().ClearBuffer(r, 1.0f, 1.0f);
    if (window.keyboard.KeyIsPressed(VK_MENU))
    {
        MessageBoxA(nullptr, "Hello World!", "Alt was pressed!", MB_OK);
    }
}
