#include <glm/glm.hpp>


class ICamera 
{
public:
    explicit ICamera() {}
    ~ICamera() {}

    [[nodiscard]] constexpr const glm::vec3& GetPosition() const noexcept { return mPosition; }
    [[nodiscard]] constexpr const glm::mat4& GetViewMatrix() const noexcept { return mViewMatrix; }
    [[nodiscard]] constexpr const glm::mat4& GetProjectionMatrix() const noexcept { return mProjectionMatrix; }
    [[nodiscard]] constexpr const glm::mat4& GetProjectionViewMatrix() const noexcept { return mProjectionMatrix * mViewMatrix; }

    virtual void Resize(const uint32_t width, const uint32_t height) = 0;

private:
    virtual void CalculateTransformMatrices() = 0;

protected:
    glm::vec3 mPosition;
    
    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix;
};