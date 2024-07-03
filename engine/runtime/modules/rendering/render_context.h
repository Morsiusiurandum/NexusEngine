/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include "command_buffer.h"
#include "../Camera.h"

import engine.core.rhi;

namespace rendering
{

    class render_context
    {
    public:
        render_context()
        {
        } ;
        void SetupCameraProperties(const Camera &camera);
        void ExecuteCommandBuffer(command_buffer buffer);

    public:
        DirectX::XMMATRIX project{};
        core::graphics *  gfx = nullptr;
    };

} // namespace rendering

#endif //RENDER_CONTEXT_H
