﻿/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <string>

class GameObject;

class Component
{
    friend GameObject;

public:
    virtual ~Component() = 0;

    std::string                 tag;
    std::shared_ptr<GameObject> game_object = nullptr;
};
#endif