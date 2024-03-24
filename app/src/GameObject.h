#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include <vector>
#include <map>
#include "Component.h"
#include "Drawable/Object/MeshRenderer.h"
#include "Drawable/Object/Transform.h"

#include <memory>

enum PrimitiveType
{
    PRIMITIVE_CUBE
};


/**
 * \brief The base class for all entities
 */
class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    GameObject()  = default;
    ~GameObject() = default;

    GameObject(const GameObject &)                     = delete;
    auto operator=(const GameObject &) -> GameObject & = delete;

    static auto CreatePrimitive(Graphics &graphics, PrimitiveType type) noexcept -> std::shared_ptr<GameObject>;

    template<typename T>
    std::shared_ptr<T> GetComponent(ComponentType type);

    void AddComponent(std::unique_ptr<Component> component);

    Transform transform;

    std::unique_ptr<DrawableBase> mesh_renderer;

private:
    std::map<ComponentType, std::shared_ptr<Component>> _component_map;

};



#endif
