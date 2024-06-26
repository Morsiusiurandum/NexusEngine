﻿#ifndef MESH_H
#define MESH_H

#include "../platform/windows/windows_platform_macro.h"

#include "Vertex.h"
#include <vector>

class Mesh
{
public:
    enum Type
    {
        CUBE_MESH
    };

    Mesh(std::vector<Vertex> vertex_in, std::vector<uint16_t> index_in);

    void UpdateTransform(DirectX::FXMMATRIX   &transform);

    /**
     * \brief Asserts face-independent vertices normals and cleared to zero
     */
    void SetNormalsIndependentFlat() noexcept(!IS_DEBUG);

private:
    std::vector<Vertex>   vertex;
    std::vector<uint16_t> index;

};
#endif
