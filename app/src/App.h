#ifndef APP_H
#define APP_H
#include "Window/Window.h"

class App
{
public:
    App();

    auto Awake() -> int;
    ~App();

private:
    auto Update() -> void;

private:
    Window                                  window;
    Timer                                   timer;
    std::vector<std::unique_ptr<class Box>> boxes;
};

#endif //APP_H
