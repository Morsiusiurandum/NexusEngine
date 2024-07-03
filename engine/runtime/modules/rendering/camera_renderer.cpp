/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#include "camera_renderer.h"

modules::camera_renderer::camera_renderer() = default;

void modules::camera_renderer::Render(rendering::render_context *context, const Camera &camera)
{
    context_ptr = context;
    camera_     = camera;

    Setup();

    /*
            PrepareBuffer();
            PrepareForSceneWindow();
            Cull();

            DrawVisibleGeometry();
            DrawUnsupportedShaders();
            DrawGizmos();
            Submit();*/
}

void modules::camera_renderer::Setup()
{
    //hand the camera's projection matrix to the context
    context_ptr->SetupCameraProperties(camera_);
    /*
     auto flags = camera_.clear_flag;
    buffer_.ClearRenderTarget
        (
            flags <= CameraClearFlags.Depth,
            flags == CameraClearFlags.Color,
            flags == CameraClearFlags.Color ? _camera.backgroundColor.linear : Color.clear
            );
     */
    context_ptr->ExecuteCommandBuffer(buffer_);
    buffer_.clean();
}
