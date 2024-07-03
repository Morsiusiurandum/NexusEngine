/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include "command_buffer.h"
#include "../Camera.h"
#include "../../platform/windows/Window.h"

#include <memory>

import engine.core.rhi;

namespace rendering
{

    class render_context
    {
    public:
        explicit render_context(Window &window);

        void setup_camera(const Camera &camera) const;

        void ExecuteCommandBuffer(command_buffer buffer);

        void draw_renderers();

        void submit() const;

    private:
        std::unique_ptr<core::graphics> graphics_ptr{};
        std::unique_ptr<command_buffer> command_buffer_{};
    };

} // namespace rendering

#endif //RENDER_CONTEXT_H
