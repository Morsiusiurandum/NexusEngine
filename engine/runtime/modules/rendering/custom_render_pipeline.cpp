/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#include "custom_render_pipeline.h"

namespace modules
{

    custom_render_pipeline::custom_render_pipeline(): camera_renderer_()
    {
    }
    void custom_render_pipeline::Render(rendering::render_context &context, const std::list<Camera> &cameras)
    {
        for (const auto camera: cameras)
        {
            camera_renderer_.Render(&context, camera);
        }
    }
}
