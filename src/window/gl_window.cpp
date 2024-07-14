#include "gl_window.hpp"

namespace mt 
{

void GLWindow::create(const char* name, uint32_t width, uint32_t height) 
{

    m_extent = {width, height};
    m_name = name;

    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_nativeWindow = glfwCreateWindow(m_extent.width, m_extent.height, m_name, nullptr, nullptr);

    glfwMakeContextCurrent(m_nativeWindow);

    glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow*) 
    {
        glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
    });

    glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow*, int key, int, int, int)
    {
        if(key == GLFW_KEY_ESCAPE) 
        {
            glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
        }
    });

	gladLoadGL(glfwGetProcAddress);
}

void GLWindow::run() 
{
    glfwPollEvents();
    glfwSwapBuffers(m_nativeWindow);
}

bool GLWindow::shouldClose() 
{
    return glfwWindowShouldClose(m_nativeWindow);
}


void GLWindow::destroy() 
{
    glfwTerminate();
    glfwDestroyWindow(m_nativeWindow);
}

}