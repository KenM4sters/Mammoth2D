#ifndef MAMMOTH_2D_INSTANCE_HPP
#define MAMMOTH_2D_INSTANCE_HPP

#include "Graphics/Renderer/SwapChain.hpp"

namespace mt 
{
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

private:
    constexpr void CreateInstance();
    constexpr bool CheckValidationLayerSupport() const;
    constexpr void ConfigureDebugMessengerCallback(VkDebugUtilsMessengerCreateInfoEXT &createInfo) const;
    constexpr void HasGLFWRequiredExtensions() const;
    constexpr const std::vector<const char*> Instance::GetAllRequiredExtensions() const;


private:
    VkInstance mInstance;

    const std::vector<const char *> mValidationLayers = {"VK_LAYER_KHRONOS_validation"};
};
}

#endif 