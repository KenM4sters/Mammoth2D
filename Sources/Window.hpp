#ifndef MAMMOTH_2D_WINDOW_HPP
#define MAMMOTH_2D_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include "Events/Bus.hpp"

#include <string>

namespace mt
{
class Window 
{
public:
    Window(const char* name, uint32_t width, uint32_t height);
    ~Window();

    Window(const Window& other) = delete;
    Window &operator=(const Window& other) = delete;

    void Init();

    inline static bool& IsRunning() { return mIsRunning; }

    void ListenToEvents() { glfwPollEvents(); }

    inline VkExtent2D GetExtent() const { return {mWidth, mHeight}; }

    inline GLFWwindow* GetNativeWindow() const { return mWindow; } 

    void CreateWindowSurface(const VkInstance instance, VkSurfaceKHR* surface) const;

    static void OnWindowCloseCallback(GLFWwindow* window);
    

private:
    GLFWwindow* mWindow = nullptr;

    uint32_t mWidth{0};
    uint32_t mHeight{0};

    const char* mName{""};

    static bool mIsRunning;
};

}

#endif