#include "App.h"
#include "Drawable/Box.h"
#include "Drawable/DrawableBase.h"
#include "Drawable/Plane.h"
#include "Drawable/Pyramid.h"
#include "NexusMath.h"
#include <memory>

App::App()
    : window(800, 600, CHAR2LPCWSTR("Start Window"))
{
    class Factory
    {
    public:
        explicit Factory(Graphics &gfx)
            : gfx(gfx)
        {
        }
        auto operator()() -> std::unique_ptr<DrawableBase>
        {
            const DirectX::XMFLOAT3 mat = {cdist(rng), cdist(rng), cdist(rng)};

            switch (typedist(rng))
            {
            case 0:
                return std::make_unique<Box>(
                    gfx,
                    rng,
                    adist,
                    ddist,
                    odist,
                    rdist,
                    bdist,
                    mat);
            case 1:
                return std::make_unique<Box>(
                    gfx,
                    rng,
                    adist,
                    ddist,
                    odist,
                    rdist,
                    bdist,
                    mat);
            case 2:
                return std::make_unique<Pyramid>(
                    gfx,
                    rng,
                    adist,
                    ddist,
                    odist,
                    rdist
                    );
            }
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

        std::uniform_int_distribution<int> typedist{0, 2};
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
        if (const auto e_code = Window::ProcessMessage())
        {
            return *e_code;
        }
        Update();
    }
}

auto App::Update() -> void
{

    const auto dt = timer.Mark();
    window.GetGraphics().ClearBuffer(0.07f, 0.0f, 0.12f);
    for (const auto &d: drawables)
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
