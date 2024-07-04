#include "PerspectiveCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

explicit PerspectiveCamera::PerspectiveCamera(const glm::vec3 position) 
    : ICamera(position), mTarget{0.0f, 0.0f, 0.0f}, mFront{0.0f, 0.0f, -1.0f}, 
    mUp{0.0f, 1.0f, 0.0f}, mZoom{45.0f}, mAspectRatio{1.0f}
{

}

PerspectiveCamera::~PerspectiveCamera() 
{

}

void PerspectiveCamera::Resize(const uint32_t width, const uint32_t height) 
{
    mAspectRatio = width / height;
    
    CalculateProjectionMatrix();
}

void PerspectiveCamera::CalculateViewMatrix() 
{
    mViewMatrix = glm::lookAt(mPosition, mTarget, mUp);
}

void PerspectiveCamera::CalculateProjectionMatrix() 
{
    mProjectionMatrix = glm::perspective(glm::radians(mZoom), mAspectRatio, 0.1f, 100.0f);
}


