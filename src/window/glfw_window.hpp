#ifndef MAMMOTH_2D_WINDOW_HPP
#define MAMMOTH_2D_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN

#include "Window.hpp"
#include "Events/Bus.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <string>


namespace mt
{
/**
 * @brief Responsible for creating the GLFW window as well as the surface that's used
 * by the renderer to display to.
*/
class GLFWWindow : public IWindow
{
public:
    /**
     * @brief Constructs the Window instance with the typical user-defined variables.
     * @param name The name of the window (doesn't matter what it is).
     * @param width The width of the window in pixels.
     * @param height The height of the window in pixels. 
    */
    GLFWWindow(const char* name, uint32_t width, uint32_t height);
    ~GLFWWindow();

    /**
     * @brief Simple call to glfwPollEvents() which is required for any glfw callbacks to work.
    */
    void ListenToEvents() { glfwPollEvents(); }

    /**
     * @brief The vulkan api has no idea where the rendering frustum is on the screen,
     * so we need to make a VkSurface that stores all of that information. 
     * This function is only called once from the Instance class. Perhaps it makes more sense
     * for this function belong there, but I wanted to keep all GLFW commands to this Window
     * class.
    */
    void CreateWindowSurface(const VkInstance instance, VkSurfaceKHR* surface) const;

    /**
     * @brief Sets mIsRunning to false and is only called by GLFW as a callback provided
     * to the glfwSetWindowCloseCallback() function.
     * @param window The GLFW window. It's not actually used since we store our own pointer
     * to the GLFW window, but the GLFW callback requires it. It doesn't matter which one
     * you use since the mWindow member variable is the only GLFWWindow that's set via
     * glfwMakeContextCurrent().
    */
    static void OnWindowCloseCallback(GLFWwindow* window);
    
    inline static bool& IsRunning() { return mIsRunning; }
    inline VkExtent2D GetExtent() const { return {mWidth, mHeight}; }
    inline GLFWwindow* GetNativeWindow() const { return mWindow; } 

private:
    GLFWwindow* mWindow = nullptr;

    uint32_t& mWidth;
    uint32_t& mHeight;

    const char* mName = "";

    static bool mIsRunning;
};

}

#endif