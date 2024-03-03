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

    const float r = sin(timer.Peek());
    window.GetGraphics().ClearBuffer(r, r, 1.0f);
    window.GetGraphics().Draw((timer.Peek()));
    window.GetGraphics().EndFrame();
    if (window.keyboard.KeyIsPressed(VK_MENU))
    {
        MessageBoxA(nullptr, "Hello World!", "Alt was pressed!", MB_OK);
    }
}
