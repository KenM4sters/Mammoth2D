#ifndef MT_GL_WINDOW_HPP
#define MT_GL_WINDOW_HPP

#include "window.hpp"

#include <GLFW/glfw3.h>

namespace mt 
{

class GLWindow final : public Window 
{
public:
    explicit GLWindow() noexcept 
        : m_extent{0, 0},
        m_name{""},
        m_nativeWindow{nullptr}
    {}

    virtual void create(const char* name, uint32_t width, uint32_t height) override;

    virtual void run() override;

    virtual bool shouldClose() override;

    virtual void destroy() override;
    
    virtual GLFWwindow* getNativeWindow() const override { return m_nativeWindow; }


private:
    Extent m_extent;
    const char* m_name;
    GLFWwindow* m_nativeWindow;
};  

}

#endif