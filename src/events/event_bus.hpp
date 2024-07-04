#pragma once
#include <list>
#include <unordered_map>
#include <typeindex>
#include "./Handler.hpp"



namespace mt
{
    
typedef std::list<IHandler*> HandlerList;

class EventBus 
{
public:

    ~EventBus() 
    {
        for(const auto& sub : mSubscribers) 
        {
            delete sub.second;
        }
    }

    template <typename EventType>
    void Publish(EventType* event)  
    {
        HandlerList* handlerList = mSubscribers[typeid(EventType)];

        if(!handlerList) 
        {
            return;
        }
        
        for(auto& handler : *handlerList) 
        {
            if(handler) 
            {
                handler->Execute(event);   
            }
        }

        delete event;
    }


    template<class T, class EventType>
    void Subscribe(T* instance, void(T::*memberFunction)(EventType*)) 
    {
        HandlerList* handlerList = mSubscribers[typeid(EventType)];

        if(!handlerList) 
        {
            handlerList = new HandlerList();
            mSubscribers[typeid(EventType)] = handlerList;
        }
        
        handlerList->push_back(new Handler<T, EventType>(instance, memberFunction));
    }

private:
    std::unordered_map<std::type_index, HandlerList*> mSubscribers;
};
}
