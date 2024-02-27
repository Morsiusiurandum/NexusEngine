#ifndef APP_H
#define APP_H
#include "Window.h"

class App
{
public:
    App();

    auto Awake() -> int;

    auto Update() -> int;

private:
    Window window_;

    Timer timer_;
};

#endif//APP_H
