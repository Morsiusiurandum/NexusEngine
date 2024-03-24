#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include <vector>
#include "Component.h"
#include "Drawable/Object/MeshRenderer.h"
#include "Drawable/Object/Transform.h"

#include <memory>

enum PrimitiveType
{
    PRIMITIVE_CUBE
};

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    GameObject()  = default;
    ~GameObject() = default;

    GameObject(const GameObject &)                     = delete;
    auto operator=(const GameObject &) -> GameObject & = delete;

    static auto CreatePrimitive(Graphics &graphics, PrimitiveType type) -> std::shared_ptr<GameObject>;

    //
    // T GetComponent();


    void AddComponent(std::unique_ptr<Component> component);

    Transform transform;

    std::unique_ptr<DrawableBase> mesh_renderer;

    //private:
    std::vector<std::unique_ptr<Component>> _component_vector;

private:
    //std::shared_ptr<GameObject> _self;
};

#endif
