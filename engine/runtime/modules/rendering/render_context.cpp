/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#include "../App.h"
#include "render_context.h"

namespace rendering
{
    render_context::render_context(Window &window)
    {
        graphics_ptr    = std::make_unique<core::graphics>(window);
        command_buffer_ = std::make_unique<command_buffer>(graphics_ptr.get());
    }

    void render_context::setup_camera(const Camera &camera) const
    {
        graphics_ptr->setup_camera(camera.GetMatrix());

        const auto dt = App::timer.Peek();
        graphics_ptr->clear_color(sin(dt), 0, 0);
    }

    void render_context::ExecuteCommandBuffer(command_buffer buffer)
    {
        buffer.BeginSample("test");
    }

    void render_context::draw_renderers()
    {
        //  App::Instance->drawables;
    }

    void render_context::submit() const
    {
        graphics_ptr->end_frame();
    }
} // namespace rendering
