#include "RenderSystem.hpp"
#include "Scene/Entity.hpp"
#include "Graphics/Buffers/Buffer.hpp"

namespace Super 
{
class PlayerSystem : public RenderSystem 
{
public:
    PlayerSystem(Device& device, VkRenderPass renderPass, uint32_t height, uint32_t width);

    ~PlayerSystem() 
    {
    }

    void CreatePlayerEntity();

    void CreatePipelineLayout() override;

    void CreatePipeline(uint32_t width, uint32_t height, VkRenderPass renderPass) override;
    
    void UpdateBuffers() override;

    void Run(VkCommandBuffer commandBuffer, std::vector<Entity>& entities) override;

private:

    void UpdatePushConstants(Entity& player);

    Entity* mPlayer = nullptr;

    std::shared_ptr<Buffer> mVertexBuffer = nullptr;

    VkVertexInputBindingDescription mVertexBindingDesc{};
    std::vector<VkVertexInputAttributeDescription> mVertexAttribsDesc{};

    SimplePushConstants mPushConstants{};
};
}