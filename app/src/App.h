#ifndef APP_H
#define APP_H

#include "Drawable/DrawableBase.h"
#include "Window/Window.h"

class App
{
public:
    App();
    ~App();

    auto Awake() -> int;

private:
    auto Update() -> void;

private:
    Window window;
    Timer  timer;

    std::vector<std::unique_ptr<class DrawableBase>> drawables;
    float                                            speed_factor = 1.0f;
    static constexpr size_t                          nDrawables   = 80;
};

#endif //APP_H
