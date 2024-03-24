#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <string>

enum ComponentType
{
    MESH
};


class GameObject;

class Component
{
    friend GameObject;

public:
    virtual ~Component() = default;

    virtual ComponentType GetType() = 0;

    std::string                 tag;
    std::shared_ptr<GameObject> game_object = nullptr;

};
#endif
