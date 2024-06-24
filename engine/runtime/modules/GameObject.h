/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../platform/windows/directx11/Graphics.h"

#include "component/Component.h"
#include "../core/Drawable/DrawableBase.h"
#include "component/Transform.h"
#include <map>

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

    GameObject(const GameObject &)                      = delete;
    GameObject(const GameObject &&)                     = delete;
    auto operator=(const GameObject &) -> GameObject &  = delete;
    auto operator=(const GameObject &&) -> GameObject & = delete;

    static auto CreatePrimitive(Graphics &graphics, PrimitiveType type) noexcept -> std::shared_ptr<GameObject>;

    auto GetComponent(const std::pmr::string &type) -> std::shared_ptr<Component>;

    void AddComponent(std::unique_ptr<Component> component);

    Transform transform;

    std::unique_ptr<DrawableBase> mesh_renderer;

private:
    std::map<std::pmr::string, std::shared_ptr<Component> > _component_map;
};

#endif
