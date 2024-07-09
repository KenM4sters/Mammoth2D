#include "graphics.hpp"


namespace mt 
{


Graphics::Graphics(GraphicsBackend backend) 
{
    Graphics::s_backend = backend;
}

Graphics::~Graphics() 
{

}

}