/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

module;

#include "../../App.h"

module engine.core.rhi;

void core::graphics::clear_depth(float depth) noexcept
{
    App::Instance->graphics_ptr->ClearBuffer(0, 0, 0);
}
void core::graphics::clear_color(float r, float g, float b)
{
    App::Instance->graphics_ptr->ClearBuffer(0, 0, 0);
}
