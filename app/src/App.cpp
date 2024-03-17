#include "App.h"
#include "Drawable/Box.h"
#include "Drawable/DrawableBase.h"
#include "NexusMath.h"
#include <memory>

App::App()
    : window(800, 600, CHAR2LPCWSTR("Start Window")), timer()
{
    class Factory
    {
    public:
        explicit Factory(Graphics &gfx)
            : gfx(gfx)
        {
        }
        std::unique_ptr<DrawableBase> operator()()
        {
            const DirectX::XMFLOAT3 mat = {cdist(rng), cdist(rng), cdist(rng)};
            return std::make_unique<Box>(
                gfx,
                rng,
                adist,
                ddist,
                odist,
                rdist,
                bdist,
                mat);
        }

    private:
        Graphics                             &gfx;
        std::mt19937                          rng{std::random_device{}()};
        std::uniform_real_distribution<float> adist{0.0f, PI * 2.0f};
        std::uniform_real_distribution<float> ddist{0.0f, PI * 0.5f};
        std::uniform_real_distribution<float> odist{0.0f, PI * 0.08f};
        std::uniform_real_distribution<float> rdist{6.0f, 20.0f};
        std::uniform_real_distribution<float> bdist{0.4f, 3.0f};
        std::uniform_real_distribution<float> cdist{0.0f, 1.0f};
    };

    drawables.reserve(nDrawables);
    std::generate_n(std::back_inserter(drawables), nDrawables, Factory{window.GetGraphics()});

    window.GetGraphics().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

App::~App() = default;

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
    for (auto &d: drawables)
    {
        d->Update(window.keyboard.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
        d->Draw(window.GetGraphics());
    }
    window.GetGraphics().EndFrame();

    if (window.keyboard.KeyIsPressed(VK_MENU))
    {
        MessageBoxA(nullptr, "Hello World!", "Alt was pressed!", MB_OK);
    }
}
