#pragma once
#include <fstream>
#include <vector>
#include "Device.hpp"
#include "VertexInput.hpp"
#include "Shader.hpp"
#include "SwapChain.hpp"

namespace Super 
{


class Pipeline 
{
public:
    Pipeline(Device& device, VkRenderPass renderPass, uint32_t width, uint32_t height, std::unique_ptr<Shader> shader, VkPipelineBindPoint bindPoint);
    ~Pipeline();

    Pipeline(const Pipeline& other) = delete;
    Pipeline& operator=(const Pipeline& other) = delete;

    void Bind(VkCommandBuffer commandBuffer);
    

    // Getters.
    //
    inline const VkPipelineLayout GetPipelineLayout() const { return mPipelineLayout; }
    inline const VkDescriptorSetLayout GetDescriptorSetLayout() const { return mDescriptorSetLayout; }
    inline const VkPipelineBindPoint GetPipelineBindPoint() const { return mPipelineBindPoint; }
    inline const VkDescriptorPool GetDecsriptorPool() const { return mDescriptorPool; }
    inline const uint32_t& GetMaxDescriptorSets() const { return mMaxSets; }


private:
    PipelineDesc SetDefaultPipelineDesc(uint32_t width, uint32_t height);

    void CreateDescriptorPool();
    void CreateDescriptorLayout();
    void CreatePipelineLayout();
    void CreateGraphicsPipeline(VkRenderPass renderPass, uint32_t width, uint32_t height);

    Device& mDevice;

    std::unique_ptr<Shader> mShader = nullptr;

    VkPipeline mPipeline = VK_NULL_HANDLE;
    VkPipelineLayout mPipelineLayout = VK_NULL_HANDLE;
    VkPipelineBindPoint mPipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

    uint32_t mMaxSets = SwapChain::FRAMES_IN_FLIGHT;
    VkDescriptorPoolSize mPoolSize{};
    VkDescriptorPool mDescriptorPool = VK_NULL_HANDLE;
    VkDescriptorSetLayout mDescriptorSetLayout = VK_NULL_HANDLE;
};
}