#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrthographicCamera 
{
public:
    /**
     * @brief Construction requires a position vector since it's all too easy to forget to 
     * set the position and wonder why nothing is within the view frustum.
     * @param position x, y and z coordiantes of the OrthographicCamera's position in world space.
     */
    explicit OrthographicCamera(glm::vec3 position, glm::vec3 target = {0.0f, 0.0f, 0.0f}) 
        : mPosition{position}, mTarget{target}, mUp{0.0f, 1.0f, 0.0f}, mNear{0.1f}, mFar{1000.0f}
    {}
    
    /**
     * @brief Computes and returns a view matrix. 
     * The view matrix is computed by using the traditional LookAt transformation
     * which considers the the position, target and up vectors of the camera.
     * Bare in mind that the target is the vector that the camera should looking at, and the 
     * up vector is relative to the camera's orientation (simply [0, 1, 0] for non-rotating cameras).
     * @returns 4x4 view matrix. 
     */
    [[nodiscard]] constexpr const glm::mat4& GetViewMatrix() const noexcept 
    { 
        return glm::lookAt(mPosition, mTarget, mUp);
    }

    /**
     * @brief Computes and returns a perspective projection matrix.
     * A projection matrix considers the distance along the z axis to the camera and scales
     * vertices further away down, given a desirable effect of perspective.
     * @param width the width of the frustum (probably just the width of the canvas).
     * @param height the height of the frustum (probably just the width of the canvas).
     * @returns 4x4 projection matrix.
     */
    [[nodiscard]] constexpr const glm::mat4& GetProjectionMatrix(const uint32_t left, 
        const uint32_t right, const uint32_t down, const uint32_t up) const noexcept 
    {
        return glm::orthoLH_ZO<float>(left, right, down, up, mNear, mFar);
    }

    
public:
    glm::vec3 mPosition;

    glm::vec3 mTarget;
    
    glm::vec3 mUp;

    float mNear;

    float mFar;
};