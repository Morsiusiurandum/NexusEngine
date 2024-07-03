/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

export module engine.core.rhi:graphics;

namespace core
{
    export class graphics
    {
    public:
        void static clear_depth(float depth) noexcept;

        void static clear_color(float r, float g, float b);

    private:
        //  std::unique_ptr<directx11::Graphics> graphics_ptr;

    };

} // namespace core
