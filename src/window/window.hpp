#ifndef MT_WINDOW_HPP
#define MT_WINDOW_HPP

#include <mammoth/mamoth.hpp>

#include <iostream>

namespace mt 
{

class IWindow 
{
    friend class GLWindow;
public:
    IWindow(const IWindow& other) = delete;
    IWindow& operator=(const IWindow& other) = delete;
    IWindow(IWindow&& other) = default;
    IWindow& operator=(IWindow&& other) = default;

    virtual void create(const char* name, uint32_t width, uint32_t height) = 0;

    virtual void destroy() = 0;

private:
    explicit IWindow() noexcept = default;

    virtual ~IWindow() {}
};

}

#endif