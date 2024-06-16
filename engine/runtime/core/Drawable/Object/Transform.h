#ifndef TRANSFORM
#define TRANSFORM

struct Transform
{
    struct Position
    {
        float x, y, z;
    }position;

    struct Rotation
    {
        float x, y, z;
    }rotation;

    struct Scale
    {
        float x = 1.0f, y = 1.0f, z = 1.0f;
    }scale;
};

#endif
