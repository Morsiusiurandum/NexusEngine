#ifndef APP_H
#define APP_H
#include "Window/Window.h"

class App
{
public:
    App();

    auto Awake() -> int;

private:
    auto Update() -> void;

private:
    Window window;
    Timer  timer;
};

#endif //APP_H
