/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#include <memory>
#include "../../platform/windows/directx11/Graphics.h"
#include "../../platform/windows/Window.h"

export module engine.core.rhi:graphics;

namespace core
{
    export class graphics
    {
    public:
        explicit graphics(Window &window);

        void clear_depth(float depth) const noexcept;

        void clear_color(float r, float g, float b) const;

        void setup_camera(const DirectX::XMMATRIX &matrix) const
        {
            graphics_ptr->SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
            graphics_ptr->SetCamera(matrix);
        }

        void end_frame() const;

    private:
        std::unique_ptr<directx11::Graphics> graphics_ptr;
    };

} // namespace core
