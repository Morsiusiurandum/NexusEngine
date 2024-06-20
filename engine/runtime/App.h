/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#ifndef APP_H
#define APP_H

#include "core/utils/Timer.h"
#include "platform/windows/Window.h"
#include "modules/Camera.h"
#include "core/Drawable/DrawableBase.h"
#include "modules/GameObject.h"
#include "modules/ImGuiManager.h"

class App
{
public:
    App();

    ~App();

    auto Awake() -> int;

private:
    void Update();

private:
    ImguiManager                               imGui_manager{};
    Camera                                     main_camera{};
    Window                                     window;
    Timer                                      timer{};
    std::vector<std::unique_ptr<DrawableBase>> drawables{};
    float                                      speed_factor = 13.0f;
    static constexpr size_t                    nDrawables   = 80;

    std::shared_ptr<GameObject> _object;
};

#endif //APP_H
