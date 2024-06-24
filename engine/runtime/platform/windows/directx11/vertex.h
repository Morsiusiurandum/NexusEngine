/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef VERTEX_H
#define VERTEX_H

#include <DirectXMath.h>

namespace windows_dirtex11
{

    /**
     *\brief Vertex data in the model.
     */
    struct vertex
    {
        /**
         * \brief Position of the point based on model space.
         */
        DirectX::XMFLOAT3 pos{0, 0, 0};

        /**
         * \brief Normal direction of the point based on model space.
         */
        DirectX::XMFLOAT3 n{0, 0, 0};

        DirectX::XMFLOAT2 tex{0, 0};

        DirectX::XMFLOAT3 color{0, 0, 0};
    };
} // namespace windows_dirtex11

#endif //VERTEX_H
