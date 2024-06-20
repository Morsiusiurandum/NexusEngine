
/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef RENDERER_H
#define RENDERER_H
#include "Component.h"

/**
* @brief The renderer is a tool that makes an object appear on the screen,
* and you can disable the renderer to make the object invisible.
 */
class renderer : public Component
{

public:
    bool enable = true;
};

#endif //RENDERER_H
