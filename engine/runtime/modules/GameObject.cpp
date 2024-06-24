/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#include "GameObject.h"

#include "../core/Drawable/Object/Box.h"
#include "../platform/windows/Window.h"
#include "component/MeshFilter.h"

#include <memory>

auto GameObject::CreatePrimitive(Graphics &graphics, const PrimitiveType type) noexcept -> std::shared_ptr<GameObject>
{
    auto ptr = std::make_shared<GameObject>();

    switch (type)
    {
    case PRIMITIVE_CUBE:
        ptr->AddComponent(std::make_unique<MeshFilter>(Mesh::CUBE_MESH));
        ptr->mesh_renderer = std::make_unique<Box>(graphics);
        break;
    }

    return ptr;
}

auto GameObject::GetComponent(const std::pmr::string &type) -> std::shared_ptr<Component>
{
    if (const auto find = _component_map.find(type); find != _component_map.end())
    {
        return find->second;
    }
    return nullptr;
}

void GameObject::AddComponent(std::unique_ptr<Component> component)
{
    if (const auto find = _component_map.find(component->GetType()); find != _component_map.end())
    {
        throw R"(The component already exists!)";
    }

    component->game_object               = shared_from_this();
    _component_map[component->GetType()] = std::move(component);
}
