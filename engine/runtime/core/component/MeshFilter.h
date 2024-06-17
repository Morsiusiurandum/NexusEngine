#ifndef COMPONENT_MESH_FILTER_H
#define COMPONENT_MESH_FILTER_H

#include "../mesh/Mesh.h"
#include "Component.h"

class MeshFilter final : public Component
{

public:
    //  ~MeshFilter() override = default;

    explicit MeshFilter(const Mesh::Type type)
    {
        switch (type)
        {
        case Mesh::CUBE_MESH:

            break;
        }
    }

    Type GetType() override
    {
        return MESH;
    }

private:
    //  Mesh _mesh;
};
#endif
