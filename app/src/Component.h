#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <string>

class GameObject;

class Component
{
    friend GameObject;

public:
    std::string                 tag;
    std::shared_ptr<GameObject> game_object = nullptr;
};
#endif
