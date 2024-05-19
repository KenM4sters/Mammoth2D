#pragma once
#include "Entity.hpp"

namespace Super 
{
class System 
{
public:
    System() {}
    virtual ~System() {}

    virtual void Update(std::vector<Entity>& entities) = 0;
};
}