#include "Camera.hpp"


namespace mt 
{
OrthographicCamera::OrthographicCamera(uint32_t width, uint32_t height, glm::vec3 position)
    : mPosition{position}
{
    RecalculateTransforms(width, height);
}

OrthographicCamera::~OrthographicCamera() 
{

}

void OrthographicCamera::RecalculateTransforms(uint32_t width, uint32_t height) 
{
    mViewMatrix = glm::lookAt(mPosition, glm::vec3(0.0f), mUp);
    mProjectionMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 1.0f);
}

}