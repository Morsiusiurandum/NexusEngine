#include "GameObject.h"

#include "Drawable/Mesh/Mesh.h"
#include "Drawable/Object/Box.h"
#include "Window/Window.h"


auto GameObject::CreatePrimitive(Graphics &graphics, const PrimitiveType type) -> std::shared_ptr<GameObject>
{
    auto ptr = shared_from_this();

    switch (type)
    {
    case PRIMITIVE_CUBE:
        ptr->_component_vector.push_back(std::make_unique<Mesh>());
        ptr->mesh_renderer = std::make_unique<Box>(graphics);
        break;
    }

    return ptr;
}

void GameObject::AddComponent(std::unique_ptr<Component> component)
{
    component->game_object = shared_from_this();
    _component_vector.push_back(std::move(component));
}
