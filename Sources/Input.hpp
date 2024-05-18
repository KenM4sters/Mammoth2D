#pragma once
#include <GLFW/glfw3.h>
#include "Events/EventSystem.hpp"

namespace Super 
{
class Input : public EventSystem
{
public:
    Input();
    ~Input();

    void ListenToKeyboard(GLFWwindow* window) const;

};
}