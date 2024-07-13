#ifndef MT_GL_WINDOW_HPP
#define MT_GL_WINDOW_HPP

#include "window.hpp"

#include <GLFW/glfw3.h>

namespace mt 
{

class GLWindow final : public IWindow 
{
public:
    explicit GLWindow() noexcept 
        : m_extent{0, 0},
        m_name{""},
        m_nativeWindow{nullptr}
    {}

    virtual void create(const char* name, uint32_t width, uint32_t height) override;

    virtual void destroy() override;

private:
    Extent m_extent;
    const char* m_name;
    GLFWwindow* m_nativeWindow;
};  

}

#endif