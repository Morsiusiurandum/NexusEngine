/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#ifndef COMMAND_BUFFER_H
#define COMMAND_BUFFER_H

#include "Color.h"

#include <string>
#include <vector>

import engine.core.rhi;

namespace rendering
{
    class command_buffer
    {
    public:
        explicit command_buffer(core::graphics *gfx);

        void clean();

        void clear_render_target(bool clearDepth, bool clearColor, Color backgroundColor, float depth) const;

        void BeginSample(std::string name);

    private:
        std::vector<int> command_;

        core::graphics *graphics_ = nullptr;
    };
}

#endif //COMMAND_BUFFER_H
