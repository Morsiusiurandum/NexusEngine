#ifndef APP_H
#define APP_H

#include "Camera.h"
#include "Drawable/DrawableBase.h"
#include "ImGuiManager.h"
#include "Drawable/Object/Box.h"
#include "Window/Window.h"

class App
{
public:
    App();
    ~App();

    auto Awake() -> int;

private:
    void Update();

private:
    ImguiManager                               imGui_manager;
    Camera                                     main_camera{};
    Window                                     window;
    Timer                                      timer{};
    std::vector<std::unique_ptr<DrawableBase>> drawables;
    float                                      speed_factor = 13.0f;
    static constexpr size_t                    nDrawables   = 80;

    std::unique_ptr<Box> _object;
};

#endif //APP_H
