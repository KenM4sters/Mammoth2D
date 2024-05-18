#include "RenderSystem.hpp"
#include "Scene/Entity.hpp"
#include "Graphics/Buffers/Buffer.hpp"

namespace Super 
{
class EnemySystem : public RenderSystem 
{
public:
    EnemySystem(Device& device, VkRenderPass renderPass, uint32_t height, uint32_t width);

    ~EnemySystem() 
    {
    }

    void CreateEnemyEntity();

    void CreatePipelineLayout() override;

    void CreatePipeline(uint32_t width, uint32_t height, VkRenderPass renderPass) override;
    
    void UpdateBuffers() override;

    void Run(VkCommandBuffer commandBuffer, std::vector<Entity>& entities) override;

private:

    void UpdatePushConstants(Entity& enemy);

    Entity* mEnemy = nullptr;

    std::shared_ptr<Buffer> mVertexBuffer = nullptr;

    VkVertexInputBindingDescription mVertexBindingDesc{};
    std::vector<VkVertexInputAttributeDescription> mVertexAttribsDesc{};

    SimplePushConstants mPushConstants{};
};
}