#ifndef MAMMOTH_2D_INPUT_HPP
#define MAMMOTH_2D_INPUT_HPP

#include <GLFW/glfw3.h>
#include "Events/Bus.hpp"
#include "Window.hpp"

namespace mt 
{
class Input 
{
public:
    Input(EventBus* eventBus, Window* window);
    ~Input();

    void ListenToKeyboard(GLFWwindow* window) const;

    static void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

};
}

#endif