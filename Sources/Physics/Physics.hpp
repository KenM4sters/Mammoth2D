#pragma once
#include "Scene/System.hpp"

#define G -0.009

namespace Super
{
class Physics : public System 
{
public:
    Physics() {}
    ~Physics() {}

    virtual void Update(std::vector<Entity>& entities) override;

private:
    void UpdateMotion(Entity& entity);
    
    void ResetMotion(Entity& entity);

    void UpdateTransformMatrix(Entity& entity);

};
}