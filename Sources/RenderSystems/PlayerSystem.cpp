#include "PlayerSystem.hpp"
#include "../EntityManager.hpp"

namespace Super
{

PlayerSystem::PlayerSystem(const std::shared_ptr<Device>& device, VkRenderPass renderPass, uint32_t height, uint32_t width)
    : RenderSystem(device, renderPass, width, height)
{
    CreatePlayerEntity();
    CreatePipelineLayout();
    CreatePipeline(width, height, renderPass);
}

void PlayerSystem::CreatePipelineLayout() 
{
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pPushConstantRanges = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;
    
    if(vkCreatePipelineLayout(mDevice->GetDevice(), &pipelineLayoutInfo, nullptr, &mPipelineLayout) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create pipeline layout!");
    }
}

void PlayerSystem::CreatePipeline(uint32_t width, uint32_t height, VkRenderPass renderPass) 
{
    Pipeline_Desc pipelineConfig = Pipeline::DefaultPipelineDesc(width, height);

    pipelineConfig.renderPass = renderPass;

    pipelineConfig.pipelineLayout = mPipelineLayout;

    mPipeline = std::make_unique<Pipeline>(
        mDevice, 
        std::move(pipelineConfig),
        "Shaders/simple.vert.spv", 
        "Shaders/simple.frag.spv"
    );
}

void PlayerSystem::UpdateBuffers() 
{
    
}

void PlayerSystem::Run(VkCommandBuffer commandBuffer) 
{
    mPipeline->Bind(commandBuffer);


    vkCmdDraw(commandBuffer, 3, 1, 0, 0);
}

void PlayerSystem::CreatePlayerEntity() 
{
    // Initial player props.
    //
    Entity* player = EntityManager::CreateEntity();
    player->flags = Entity_Flags::ACTIVE | Entity_Flags::HAS_HEALTH | Entity_Flags::IS_RIGID 
                    | Entity_Flags::HAS_MOTION | Entity_Flags::PLAYER_CONTROLLED;
    player->color = glm::vec3(0.5f, 0.1f, 1.0f);
    player->position = glm::vec2(400, 400);
    player->size = glm::vec2(50, 50);
    player->physics = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};

    // Player renderables.
    //
    std::vector<Vertex> vertices = 
    {
        {{0.0f, 1.0f}},
        {{1.0f, 0.0f}},
        {{0.0f, 0.0f}},

        {{0.0f, 1.0f}},
        {{1.0f, 1.0f}},
        {{1.0f, 0.0f}},
    };

    

}
}