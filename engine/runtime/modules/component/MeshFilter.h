/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef COMPONENT_MESH_FILTER_H
#define COMPONENT_MESH_FILTER_H

#include "../../core/mesh/Mesh.h"
#include "Component.h"

class MeshFilter final : public Component
{

public:
    explicit MeshFilter(const Mesh::Type type)
    {
        switch (type)
        {
        case Mesh::CUBE_MESH:

            break;
        }
    }

    ~MeshFilter()  
    {
        mesh = nullptr;
    }

    auto GetType() -> std::pmr::string override
    {
        return "component_mesh_filter";
    }

    /**
     * @brief The mesh object owned by the current component
     */
    Mesh *mesh = nullptr;
};
#endif
