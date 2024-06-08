#include <iostream>
#include "Input.hpp"

namespace mt 
{

static EventBus* sEventBus = nullptr;
static Window* sWindow = nullptr;

Input::Input(EventBus* eventBus, Window* window)  
{
    sEventBus = eventBus;
    sWindow = window;

    glfwSetKeyCallback(window->GetNativeWindow(), KeyPressCallback);
}

void Input::ListenToKeyboard(GLFWwindow* window) const 
{
    // if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
    //     mEventBus->Publish(new KeyPressEvent(GLFW_KEY_A));
    // if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
    //     mEventBus->Publish(new KeyPressEvent(GLFW_KEY_S));
    // if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
    //     mEventBus->Publish(new KeyPressEvent(GLFW_KEY_D));
}

void Input::KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    switch(key) 
    {
        case GLFW_KEY_W: sEventBus->Publish(new KeyPressEvent(GLFW_KEY_W)); break;
        case GLFW_KEY_A: sEventBus->Publish(new KeyPressEvent(GLFW_KEY_A)); break;
        case GLFW_KEY_D: sEventBus->Publish(new KeyPressEvent(GLFW_KEY_D)); break;
        case GLFW_KEY_ESCAPE: sWindow->IsRunning() = false; break;
    }
}
    
}