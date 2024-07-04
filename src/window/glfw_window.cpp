#include <stdexcept>
#include "GLFWWindow.hpp"

namespace mt 
{
bool GLFWWindow::mIsRunning = true;

GLFWWindow::GLFWWindow(const char* name, uint32_t width, uint32_t height)
    : mWidth{width}, mHeight{height}, mName{name}
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    mWindow = glfwCreateWindow(mWidth, mHeight, mName, nullptr, nullptr);

    glfwMakeContextCurrent(mWindow);

    glfwSetWindowCloseCallback(mWindow, GLFWWindow::OnWindowCloseCallback);
}

GLFWWindow::~GLFWWindow()
{
    glfwDestroyWindow(mWindow);
}

void GLFWWindow::CreateWindowSurface(const VkInstance instance, VkSurfaceKHR* surface) const 
{
    if(glfwCreateWindowSurface(instance, mWindow, nullptr, surface) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create window surface from glfw!");
    }
}

void GLFWWindow::OnWindowCloseCallback(GLFWwindow* window) 
{
    mIsRunning = false;
}

}