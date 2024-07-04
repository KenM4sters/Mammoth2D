#include <glm/glm.hpp>


class ICamera 
{
public:
    /**
     * @brief Construction requires a position vector since it's all too easy to forget to 
     * set the position and wonder why nothing is within the view frustum.
     * @param position x, y and z coordiantes of the camera's position in world space.
     */
    explicit ICamera(glm::vec3 position) : mPosition{position} {}

    virtual ~ICamera() {}

    [[nodiscard]] constexpr const glm::vec3& GetPosition() const noexcept { return mPosition; }
    
    [[nodiscard]] constexpr const glm::mat4& GetViewMatrix() const noexcept { return mViewMatrix; }
    
    [[nodiscard]] constexpr const glm::mat4& GetProjectionMatrix() const noexcept { return mProjectionMatrix; }
    
    [[nodiscard]] constexpr const glm::mat4& GetProjectionViewMatrix() const noexcept { return mProjectionMatrix * mViewMatrix; }

    constexpr void SetPosition(const glm::vec3 position) noexcept { mPosition = position;  }
    
    constexpr void SetViewMatrix(const glm::mat4& view) noexcept { mViewMatrix = view;  }
    
    constexpr void SetProjectionMatrix(const glm::mat4& projection) noexcept { mProjectionMatrix = projection;  }

    /**
     * @brief Resizes the camera's view frustum to the new dimensions.
     * @param width The new width of the frustum.
     * @param height The new height of the frustum.
     */
    virtual void Resize(const uint32_t width, const uint32_t height) = 0;

private:
    /**
     * @brief Calculates the view matrix based on the current state of the 
     * appropriate member variables, depending on the type of camera being used. 
     * (seperated since the view matrix is likely to change far more often than the projection
     * matrix).
     */
    virtual void CalculateViewMatrix() = 0;

    /**
     * @brief Calculates the projection matrix based on the current state of the 
     * appropriate member variables, depending on the type of camera being used.
     * (seperated since the view matrix is likely to change far more often than the projection
     * matrix). 
     */
    virtual void CalculateProjectionMatrix() = 0;

protected:
    glm::vec3 mPosition;

    glm::mat4 mViewMatrix;
    
    glm::mat4 mProjectionMatrix;
};