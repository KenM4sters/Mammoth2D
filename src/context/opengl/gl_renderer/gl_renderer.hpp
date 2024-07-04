#include "graphics/renderer.hpp"

class GLRenderer final : public IRenderer
{
public:
    GLRenderer();

    virtual ~GLRenderer() override;

    virtual void Update() override;

    virtual void Resize(const uint32_t width, const uint32_t height) override;
    
private:
    
};