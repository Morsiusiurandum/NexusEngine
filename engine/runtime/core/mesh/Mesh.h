/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef MESH_H
#define MESH_H

#include "../platform/windows/windows_platform_macro.h"

#include "../../platform/windows/directx11/vertex.h"

#include <vector>

class Mesh
{
public:
    enum Type
    {
        CUBE_MESH
    };

    Mesh(std::vector<windows_dirtex11::vertex> vertex_in, std::vector<uint16_t> index_in);

    void UpdateTransform(DirectX::FXMMATRIX &transform);

    /**
     * \brief Asserts face-independent vertices normals and cleared to zero
     */
    void SetNormalsIndependentFlat() noexcept(!IS_DEBUG);

private:
    std::vector<windows_dirtex11::vertex> vertex;
    std::vector<uint16_t>                 index;

};
#endif
