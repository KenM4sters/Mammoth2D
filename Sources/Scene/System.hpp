#pragma once
#include "Core.hpp"
#include "Events/Bus.hpp"

namespace Super 
{
class System 
{
public:
    System(EventBus& eventBus) : mEventBus{eventBus} {}
    
    virtual ~System() {}

    virtual void Update(std::vector<Entity>& entities) = 0;

protected:
    EventBus& mEventBus;
};
}