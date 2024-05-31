#pragma once
#include <string>
#include "../Core.hpp"

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
    CollisionEvent(Manifold* manifold)
        : mEntityA{manifold->pair.A}, mEntityB{manifold->pair.B}, penetration{manifold->penetration}, normal{manifold->normal} 
    {
        delete manifold;
    }

    inline const std::string GetEventType() const override { return "CollisionEvent";}

    Entity* mEntityA = nullptr;
    Entity* mEntityB = nullptr;
    float penetration;
    glm::vec2 normal;
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