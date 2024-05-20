#pragma once
#include <GLFW/glfw3.h>
#include "Events/Bus.hpp"

namespace Super 
{
class Input 
{
public:
    Input(EventBus& eventBus);
    ~Input();

    void ListenToKeyboard(GLFWwindow* window) const;
    
private:
    EventBus& mEventBus;
};
}