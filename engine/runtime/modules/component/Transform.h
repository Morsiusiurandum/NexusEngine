/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef TRANSFORM
#define TRANSFORM

/**
 * \brief Information about the position of the current object in world space
 */
struct Transform
{
    struct Position
    {
        float x = 0.0f, y = 0.0f, z = 0.0f;
    } position{};

    struct Rotation
    {
        float x = 0.0f, y = 0.0f, z = 0.0f;
    } rotation{};

    struct Scale
    {
        float x = 1.0f, y = 1.0f, z = 1.0f;
    } scale;
};

#endif
