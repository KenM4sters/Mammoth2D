#include "Core.hpp"

#include <iostream>

class IRenderer : public NonCopyable 
{
public:
    IRenderer() {}
    
    virtual ~IRenderer() {}

    virtual void Update() = 0;

    virtual void Resize(const uint32_t width, const uint32_t height) = 0;
};