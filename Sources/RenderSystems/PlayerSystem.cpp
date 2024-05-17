#include "PlayerSystem.hpp"
#include "../EntityManager.hpp"
#include "../Entity.hpp"

static Super::Vertex_Buffer_Desc vertexDesc{};

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

    // Vertex Info.
    //
    pipelineConfig.vertexInfo.vertexAttributeDescriptionCount = vertexDesc.attribsDesc.size();
    pipelineConfig.vertexInfo.vertexBindingDescriptionCount = 1;
    pipelineConfig.vertexInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    pipelineConfig.vertexInfo.pVertexBindingDescriptions = &vertexDesc.bindingDesc;
    pipelineConfig.vertexInfo.pVertexAttributeDescriptions = vertexDesc.attribsDesc.data();

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

    VkBuffer buffers[] = {mPlayer->renderable.vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
    vkCmdDraw(commandBuffer, 6, 1, 0, 0);
}

void PlayerSystem::CreatePlayerEntity() 
{
    // Initial player props.
    //
    mPlayer = new Entity{};
    mPlayer->id = EntityManager::CreateEntity(mPlayer);
    mPlayer->flags = Entity_Flags::ACTIVE | Entity_Flags::HAS_HEALTH | Entity_Flags::IS_RIGID 
                    | Entity_Flags::HAS_MOTION | Entity_Flags::PLAYER_CONTROLLED;
    mPlayer->color = glm::vec3(0.5f, 0.1f, 1.0f);
    mPlayer->position = glm::vec2(400, 400);
    mPlayer->size = glm::vec2(50, 50);
    mPlayer->physics = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};

    std::vector<BufferAttribute> attribs = 
    {
        BufferAttribute(0, VK_FORMAT_R32G32_SFLOAT),
    };

    BufferLayout layout = BufferLayout(attribs);

    layout.SetVertexBufferDesc(&vertexDesc);

    SetVertexBufferFromVertices(mDevice, mPlayer->renderable.vertexBuffer, mPlayer->renderable.vertexBufferMemory, SQUARE_VERTICES);


}
}