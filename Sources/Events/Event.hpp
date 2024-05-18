#pragma once
#include <string>
#include "../Scene/Entity.hpp"

namespace Super
{
class IEvent 
{
public:
    virtual inline const std::string GetEventType() const = 0;

    bool mHandled = false;
};


class CollisionEvent : public IEvent 
{
public:
    CollisionEvent(Entity* A, Entity* B)
        : mEntityA{A}, mEntityB{B} 
    {}

    inline const std::string GetEventType() const override { return "CollisionEvent";}

    Entity* mEntityA = nullptr;
    Entity* mEntityB = nullptr;
};

class KeyPressEvent : public IEvent 
{
public:
    KeyPressEvent(const int key)
        : mKey{key} 
    {}

    inline const std::string GetEventType() const override { return "KeyPressEvent";}

    int mKey{0};
};

}