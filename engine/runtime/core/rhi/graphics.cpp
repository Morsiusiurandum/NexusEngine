/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

module;

#include <memory>

module engine.core.rhi;

core::graphics::graphics(Window &window)
{
    graphics_ptr = std::make_unique<directx11::Graphics>(window.h_wnd, window.width, window.height);
}
void core::graphics::clear_depth(float depth) const noexcept
{
    graphics_ptr->ClearBuffer(0, 0, 0);
}
void core::graphics::clear_color(const float r, const float g, const float b) const
{
    graphics_ptr->ClearBuffer(r, g, b);
}
void core::graphics::end_frame() const
{
    graphics_ptr->EndFrame();
}
