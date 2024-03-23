#include "App.h"
#include "Drawable/DrawableBase.h"
#include "Drawable/Mesh/Plane.h"
#include "Drawable/Object/Box.h"
#include "Drawable/Object/Drawing.h"
#include "Drawable/Object/Pyramid.h"
#include "NexusMath.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <memory>
#include <random>
#include <vector>

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
                return std::make_unique<Drawing>(gfx, rng, adist, ddist, odist, rdist);
            case 1:
            // return std::make_unique<Box>(gfx, rng, adist, ddist, odist, rdist, bdist, mat);
            case 2:
                return std::make_unique<Pyramid>(gfx, rng, adist, ddist, odist, rdist);
            }
            return {};
        }

    private:
        Graphics &                            gfx;
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
    _object = std::make_unique<Box>(window.GetGraphics());

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

    const auto dt = timer.Mark() * speed_factor;
    window.GetGraphics().ClearBuffer(0, 0, 0);
    window.GetGraphics().SetCamera(main_camera.GetMatrix());

    // for (const auto &d: drawables)
    // {
    //
    //     d->Update(window.keyboard.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
    //     d->Draw(window.GetGraphics());
    // }

    _object->transform.position.x = 3 * sin(timer.Peek() * speed_factor);
    _object->transform.position.y = 3 * cos(timer.Peek() * speed_factor);
    _object->Draw(window.GetGraphics());

    // imgui window to control simulation speed
    if (ImGui::Begin("Simulation Speed"))
    {
        ImGui::SliderFloat("Speed Factor", &speed_factor, 0.0f, 15.0f);
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Status: %s", window.keyboard.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING (hold spacebar to pause)");
    }
    ImGui::End();
    //
    //    ImGui_ImplDX11_NewFrame();
    //    ImGui_ImplWin32_NewFrame();
    //    ImGui::NewFrame();
    //
    //    static bool show_demo_window = true;
    //    if (show_demo_window)
    //    {
    //        ImGui::ShowDemoWindow(&show_demo_window);
    //    }
    //    ImGui::Render();
    //    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    main_camera.SpawnControlWindow();

    window.GetGraphics().EndFrame();

    if (window.keyboard.KeyIsPressed(VK_MENU))
    {
        MessageBoxA(nullptr, "Hello World!", "Alt was pressed!", MB_OK);
    }
}
