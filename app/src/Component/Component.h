#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <string>


class GameObject;

class Component
{
    friend GameObject;

public:
    enum Type
    {
        MESH
    };

   // virtual      ~Component() = 0;
    virtual Type GetType() = 0;

     


    std::string                 tag;
    std::shared_ptr<GameObject> game_object = nullptr;

};
#endif
