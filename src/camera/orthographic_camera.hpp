#ifndef MAMMOTH_2D_CAMERA_HPP
#define MAMMOTH_2D_CAMERA_HPP

#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace mt 
{

/**
 * @brief This is currently the only type of camera support by Mammoth2D at the moment, since
 * it is only a 2D engine and doesn't need a perspective projection per se, but I'll probably implement
 * a perspective one anyway at some point as it could be useful in specific use cases.
*/
class OrthographicCamera 
{
public:
    /**
     * @brief Constructs an OrthographicCamera which holds the necessary projection matrix among other
     * relevant but not required variables.
     * @param width The width of the window which is used as the width of the camera view.
     * @param height The height of the window which is used as the height of the camera view.
     * @param position Not necessary, but if you chose to provide it then make sure the z position is positive.
    */
    OrthographicCamera(uint32_t width, uint32_t height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 2.0f));
    ~OrthographicCamera();

    inline const glm::mat4& GetViewMatrix() const { return mViewMatrix; }
    inline const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
    inline const glm::mat4 GetProjectionViewMatrix() const { return mProjectionMatrix * mViewMatrix;}
    inline const glm::vec3& GetPosition() const { return mPosition; }

private:
    /**
     * @brief Used to initially set the projection and view matrices and is required when 
     * the camera changes position or its aspect ratio changes. Neither of these are something
     * that's available at the moment.
     * @param width The width of the window which is used as the width of the camera view.
     * @param height The height of the window which is used as the height of the camera view.
    */
    void RecalculateTransforms(uint32_t width, uint32_t height);

    glm::mat4 mViewMatrix{1.0f};
    glm::mat4 mProjectionMatrix{1.0f};
    glm::vec3 mPosition;

    glm::vec3 mUp{0.0f, -1.0f, 0.0f};
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};

};
}

#endif