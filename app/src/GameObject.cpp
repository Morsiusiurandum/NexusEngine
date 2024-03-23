#include "GameObject.h"

#include "Drawable/Object/Box.h"
#include "Window/Window.h"

GameObject::GameObject(Graphics &graphics, const PrimitiveType type)
    : transform()
{
    switch (type)
    {
    case PRIMITIVE_CUBE:
        mesh = Mesh();
        mesh_renderer = std::make_unique<Box>(graphics);
        break;
    }
}

GameObject GameObject::CreatePrimitive(PrimitiveType type)
{
    return GameObject();
}
