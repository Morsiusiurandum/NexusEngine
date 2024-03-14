#include "App.h"
#include "Drawable/Box.h"
#include <memory>

App::App()
    : window(800, 600, CHAR2LPCWSTR("Start Window")), timer()
{
    std::mt19937                          rng(std::random_device{}());
    std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
    std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
    for (auto i = 0; i < 40; i++)
    {
        boxes.push_back(std::make_unique<Box>(
            window.GetGraphics(), rng, adist,
            ddist, odist, rdist));
    }
    window.GetGraphics().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

App::~App()
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

    auto dt = timer.Mark();
    window.GetGraphics().ClearBuffer(0.07f, 0.0f, 0.12f);
    for (auto &box: boxes)
    {
        box->Update(dt);
        box->Draw(window.GetGraphics());
    }

    window.GetGraphics().EndFrame();

    if (window.keyboard.KeyIsPressed(VK_MENU))
    {
        MessageBoxA(nullptr, "Hello World!", "Alt was pressed!", MB_OK);
    }
}
