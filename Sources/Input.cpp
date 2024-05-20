#include <iostream>
#include "Input.hpp"

namespace Super 
{
    Input::Input(EventBus& eventBus) : mEventBus{eventBus} 
    {

    }

    Input::~Input() 
    {

    }

    void Input::ListenToKeyboard(GLFWwindow* window) const 
    {
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
            mEventBus.Publish(new KeyPressEvent(GLFW_KEY_W));
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
            mEventBus.Publish(new KeyPressEvent(GLFW_KEY_A));
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
            mEventBus.Publish(new KeyPressEvent(GLFW_KEY_S));
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
            mEventBus.Publish(new KeyPressEvent(GLFW_KEY_D));
    }
}