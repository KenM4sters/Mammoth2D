#pragma once
#include <iostream>
#include "Bus.hpp"
#include "Event.hpp"

namespace Super 
{
class EventSystem 
{
public:
    EventSystem() 
    {
        if(!mEventBus) 
        {
            mEventBus = std::make_unique<EventBus>();
        }
    }
    
    virtual ~EventSystem() {}

protected:
    static std::unique_ptr<EventBus> mEventBus;
};
}