#ifndef MAMMOTH_2D_INSTANCE_HPP
#define MAMMOTH_2D_INSTANCE_HPP

#include "Graphics/Renderer/SwapChain.hpp"

namespace mt 
{

/**
 * @brief Responsible for creating a vulkan runtime instance (required for any communcation
 * with vulkan) and handling validation layers and extension requirements.
 * By default, the vulkan api provides very little debugging information.
*/
class Instance 
{
public:
    #ifdef NDEBUG
    const bool mEnableValidationLayers = false;
    #else
    const bool mEnableValidationLayers = true;
    #endif

public:
    Instance();
    ~Instance();

    inline const VkInstance& GetInstance() const { return mInstance; }
    inline const std::vector<const char*>& GeValidationLayers() const { return mValidationLayers; }
    const std::vector<const char*> Instance::GetAllRequiredExtensions() const;

private:
    /**
     * @brief Creates a VkInstance from some application settings and sets extensions.
    */
    void CreateInstance();

    /**
     * @brief Checks what validation layers (debug features) are supported by the instance.
    */
    bool CheckValidationLayerSupport() const;

    /**
     * @brief Sets a callback which defines the format of each validation message.
    */
    void ConfigureDebugMessengerCallback(VkDebugUtilsMessengerCreateInfoEXT &createInfo) const;

    /**
     * @brief GLFW requires some extensions to be available, so this checks whether that's true
     * or not for our instance.
    */
    void HasGLFWRequiredExtensions() const;

private:
    VkInstance mInstance;

    const std::vector<const char *> mValidationLayers = {"VK_LAYER_KHRONOS_validation"};
};
}

#endif 