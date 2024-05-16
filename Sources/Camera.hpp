#pragma once
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Super 
{
class OrthographicCamera 
{
public:
    OrthographicCamera(uint32_t width, uint32_t height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 2.0f));
    ~OrthographicCamera();

    inline const glm::mat4& GetViewMatrix() const { return mViewMatrix; }
    inline const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
    inline const glm::vec3& GetPosition() const { return mPosition; }

private:
    void RecalculateTransforms(uint32_t width, uint32_t height);

    glm::mat4 mViewMatrix{1.0f};
    glm::mat4 mProjectionMatrix{1.0f};
    glm::vec3 mPosition;

    glm::vec3 mUp{0.0f, -1.0f, 0.0f};
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};

};
}