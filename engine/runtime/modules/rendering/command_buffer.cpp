/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */
#include "command_buffer.h"

import engine.core.rhi;

rendering::command_buffer::command_buffer(core::graphics *gfx)
{
    graphics_ = gfx;
}
void rendering::command_buffer::clean()
{
    command_.clear();
}

void rendering::command_buffer::clear_render_target(bool clearDepth, bool clearColor, Color backgroundColor, float depth) const
{
    if (clearDepth)
    {
        graphics_->clear_depth(depth);
    }
    if (clearColor)
    {
        graphics_->clear_color(0, 0, 0);
    }

}
void rendering::command_buffer::BeginSample(std::string name)
{

}
