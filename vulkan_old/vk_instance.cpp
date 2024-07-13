#include "Instance.hpp"

#include <iostream>
#include <unordered_set>

namespace mt 
{

// Local callback functions.
// ----------------------------------------------------------------
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData) 
{
  std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

  return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pDebugMessenger) 
{
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance,
      "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

Instance::Instance() 
{
    CreateInstance();
}

Instance::~Instance() 
{
    vkDestroyInstance(mInstance, nullptr);
}

void Instance::CreateInstance() 
{
    if (mEnableValidationLayers && !CheckValidationLayerSupport()) 
    {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Super 2D Game";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = GetAllRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR; 

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (mEnableValidationLayers) 
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(mValidationLayers.size());
        createInfo.ppEnabledLayerNames = mValidationLayers.data();

        ConfigureDebugMessengerCallback(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
    } 
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &mInstance) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create instance!");
    }

    HasGLFWRequiredExtensions();
}

bool Instance::CheckValidationLayerSupport() const 
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : mValidationLayers) 
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) 
        {
            if (strcmp(layerName, layerProperties.layerName) == 0) 
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) 
        {
            return false;
        }
    }

    return true;
}

void Instance::ConfigureDebugMessengerCallback(VkDebugUtilsMessengerCreateInfoEXT &createInfo) const 
{
    createInfo = {};
    createInfo.sType            = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

    createInfo.messageSeverity  = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT 
                                    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

    createInfo.messageType      = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT 
                                    | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT 
                                    | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

    createInfo.pfnUserCallback = DebugCallback;
    createInfo.pUserData = nullptr;  // Optional
}

void Instance::HasGLFWRequiredExtensions() const 
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "available extensions:" << std::endl;
    std::unordered_set<std::string> available;
    for (const auto &extension : extensions) 
    {
        std::cout << "\t" << extension.extensionName << std::endl;
        available.insert(extension.extensionName);
    }

    std::cout << "required extensions:" << std::endl;
    auto requiredExtensions = GetAllRequiredExtensions();
    for (const auto &required : requiredExtensions) 
    {
        std::cout << "\t" << required << std::endl;
        if (available.find(required) == available.end()) 
        {
            throw std::runtime_error("Missing required glfw extension");
        }
    }
}

const std::vector<const char*> Instance::GetAllRequiredExtensions() const 
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (mEnableValidationLayers) 
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    }

    return extensions;
}

}