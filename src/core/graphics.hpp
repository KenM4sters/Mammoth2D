#ifndef MAMMOTH_2D_GRAPHICS_HPP
#define MAMMOTH_2D_GRAPHICS_HPP

#include "api.hpp"

namespace mt 
{

class Graphics final
{
public:
    explicit Graphics(GraphicsBackend backend);
    ~Graphics();


private:
    static GraphicsBackend s_backend;

};

}

#endif