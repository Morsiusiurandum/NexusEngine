#ifndef MESH_H
#define MESH_H

#include "../../Component.h"

class Mesh final : public Component
{
    ComponentType GetType() override
    {
        return MESH;
    }

public:
    int a = 5;

};
#endif
