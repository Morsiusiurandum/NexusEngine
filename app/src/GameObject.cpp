#include "GameObject.h"

#include "Drawable/Object/Box.h"
#include "Window/Window.h"
#include "Drawable/Mesh/Mesh.h"

#include <memory>


auto GameObject::CreatePrimitive(Graphics &graphics, const PrimitiveType type) noexcept -> std::shared_ptr<GameObject>
{
    auto ptr = std::make_shared<GameObject>();

    switch (type)
    {
    case PRIMITIVE_CUBE:
        ptr->AddComponent(std::make_unique<Mesh>());
        ptr->mesh_renderer = std::make_unique<Box>(graphics);
        break;
    }

    return ptr;
}

template<typename T>
std::shared_ptr<T> GameObject::GetComponent(const ComponentType type)
{
    if (const auto find = _component_map.find(type); find != _component_map.end())
    {
        return std::dynamic_pointer_cast<T>(find->second);
    }
    return nullptr;
}

void GameObject::AddComponent(std::unique_ptr<Component> component)
{
    if (const auto find = _component_map.find(component->GetType()); find != _component_map.end())
    {
        throw "The component already exists！";
    }

    component->game_object               = shared_from_this();
    _component_map[component->GetType()] = std::move(component);

}

template std::shared_ptr<Mesh> GameObject::GetComponent(ComponentType type);
