#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Drawable/Mesh/Mesh.h"
#include "Drawable/Object/MeshRenderer.h"
#include "Drawable/Object/Transform.h"

enum PrimitiveType
{
    PRIMITIVE_CUBE
};

class GameObject
{
public:
    GameObject()  = default;
    ~GameObject() = default;


    GameObject(Graphics &graphics, PrimitiveType type);

    static GameObject CreatePrimitive(PrimitiveType type);

    // template<class T>
    // T GetComponent();

    Transform                     transform;
    std::unique_ptr<DrawableBase> mesh_renderer;
    Mesh                          mesh;
};


#endif
