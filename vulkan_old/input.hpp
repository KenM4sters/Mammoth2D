#ifndef MAMMOTH_2D_INPUT_HPP
#define MAMMOTH_2D_INPUT_HPP

#include <GLFW/glfw3.h>

namespace mt 
{

/**
 * @brief Manages input for the engine. This will be heavily revamped in the future to handle
 * more input types (e.g: mouse position), as well as to provide a more feature-rich api for
 * games to utilize. You should only interact with this class via the main Engine instance.
*/
class Input 
{
public:
    /**
     * @brief Constructs the Input instance that the engine coordiantes with listen to user input.
     * @param eventBus a pointer to the EventBus instance that the engine holds (should only ever be one).
     * @param window a pointer to the window instance that the engine holds (should only be one, for now at least).
    */
    Input(EventBus* eventBus, Window* window);

    /**
     * @brief Calls simple GLFW functions to query user input. Keep in mind that these
     * calls will be made per frame, and merely query the state of a/many keys, meaning that calls
     * made as a result of a certain condition being satisfied (e.g: the W key is currently down)
     * will be made PER FRAME. Please see KeyPressCallback() for per event triggers. 
    */
    void ListenToKeyboard(GLFWwindow* window) const;

    /**
     * @brief Querys the state of a GLFW Key via a callback which GLFW makes once any key has
     * been pressed. Some of the parameters here are more niche and not used, but GLFW provides
     * use with them anyway. Typically we're only intersted in the key and the state (action)
     * of it. This is useful for times where you don't want to caputre events per frame that the key
     * is pressed for, and only once upon the key being pressed.
     * @param window Not really needed, but the callback that GLFW provides requires it.
     * @param key The GLFW key that has been pressed.
     * @param scancode GLFW code for the key - not important but again must be present for GLFW.
     * @param action the type of event associated with the key. Typicaly you'll only want to know
     * if it's equal GLFW_PRESS, but GLFW_RELEASE is also a valid check.
    */
    static void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

};
}

#endif