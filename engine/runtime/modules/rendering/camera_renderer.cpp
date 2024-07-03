/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#include "camera_renderer.h"

void modules::camera_renderer::Render(rendering::render_context *context, const Camera &camera)
{

    context->setup_camera(camera);

    context->draw_renderers();

    context->submit();

}
