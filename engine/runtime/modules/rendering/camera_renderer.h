/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#ifndef CAMERA_RENDERER_H
#define CAMERA_RENDERER_H

#include "command_buffer.h"
#include "render_context.h"
#include "../Camera.h"

#include<memory>

namespace modules
{
    class camera_renderer
    {
    public:
        void Render(rendering::render_context *context, const Camera &camera);;
    };
} // namespace modules

#endif //CAMERA_RENDERER_H
