#ifndef APP_H
#define APP_H

#include "Drawable/DrawableBase.h"
#include "ImGuiManager.h"
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
    ImguiManager imGui_manager;

    Window                                     window;
    Timer                                      timer{};
    std::vector<std::unique_ptr<DrawableBase>> drawables;
    float                                      speed_factor = 13.0f;
    static constexpr size_t                    nDrawables   = 80;
};

#endif //APP_H
