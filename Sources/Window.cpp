#include <stdexcept>
#include "Window.hpp"

namespace mt 
{
bool Window::mIsRunning = true;

Window::Window(const char* name, uint32_t width, uint32_t height)
    : mWidth{width}, mHeight{height}, mName{name}
{
    Init();
}

Window::~Window()
{
    glfwDestroyWindow(mWindow);
}


void Window::Init()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    mWindow = glfwCreateWindow(mWidth, mHeight, mName, nullptr, nullptr);

    glfwMakeContextCurrent(mWindow);

    glfwSetWindowCloseCallback(mWindow, Window::OnWindowCloseCallback);
}


void Window::CreateWindowSurface(const VkInstance instance, VkSurfaceKHR* surface) const 
{
    if(glfwCreateWindowSurface(instance, mWindow, nullptr, surface) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create window surface from glfw!");
    }
}

void Window::OnWindowCloseCallback(GLFWwindow* window) 
{
    mIsRunning = false;
}

}