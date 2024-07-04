#include "Camera.hpp"



class PerspectiveCamera final : public ICamera 
{
public:
    explicit PerspectiveCamera(glm::vec3 position);

    ~PerspectiveCamera();

    virtual void Resize(const uint32_t width, const uint32_t height) override;

private:
    virtual void CalculateViewMatrix() override;

    virtual void CalculateProjectionMatrix() override;

private:
    glm::vec3 mTarget;
    glm::vec3 mFront;
    glm::vec3 mUp;
    float mZoom;
    float mAspectRatio;
};