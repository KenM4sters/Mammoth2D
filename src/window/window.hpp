#ifndef MT_WINDOW_HPP
#define MT_WINDOW_HPP

#include <mammoth/mamoth.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

namespace mt 
{

class Window 
{
    friend class GLWindow;
public:
    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;
    Window(Window&& other) = default;
    Window& operator=(Window&& other) = default;

    virtual void create(const char* name, uint32_t width, uint32_t height) = 0;

    virtual void run() = 0;

    virtual bool shouldClose() = 0;

    virtual void destroy() = 0;
    
    virtual GLFWwindow* getNativeWindow() const = 0;

    virtual ~Window() {}
private:
    explicit Window() noexcept = default;
    

};

}

#endif