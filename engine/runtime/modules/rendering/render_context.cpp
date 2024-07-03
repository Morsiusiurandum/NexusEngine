/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#include "render_context.h"

namespace rendering
{
    void render_context::SetupCameraProperties(const Camera &camera)
    {
        project = camera.GetMatrix();
    }
    void render_context::ExecuteCommandBuffer(command_buffer buffer)
    {

    }
} // rendering namespace
