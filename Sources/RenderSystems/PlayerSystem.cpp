#include "PlayerSystem.hpp"
#include "../EntityManager.hpp"
#include "BufferLayout.hpp"


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
    pipelineConfig.vertexInfo.vertexAttributeDescriptionCount = mVertexAttribsDesc.size();
    pipelineConfig.vertexInfo.vertexBindingDescriptionCount = 1;
    pipelineConfig.vertexInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    pipelineConfig.vertexInfo.pVertexBindingDescriptions = &mVertexBindingDesc;
    pipelineConfig.vertexInfo.pVertexAttributeDescriptions = mVertexAttribsDesc.data();

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

    VkBuffer buffers[] = {mVertexBuffer->GetBuffer()};
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
    mPlayer->color = glm::vec3(0.5f, 0.1f, 1.0f);
    mPlayer->transform = {glm::vec2(400, 400), glm::vec2(50, 50), glm::mat3{1.0f}};
    mPlayer->physics = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};
    mPlayer->flags = EntityFlags::ACTIVE | EntityFlags::HAS_HEALTH | EntityFlags::IS_RIGID 
                    | EntityFlags::HAS_MOTION | EntityFlags::PLAYER_CONTROLLED;


    // A buffer layout takes in a vector of buffer attributes, where each buffer attribute
    // describes a portion (or in this simple case 100%) of the vertex data (position, color, normals etc..)
    //
    std::vector<BufferAttribute> attribs = 
    {
        BufferAttribute(0, VK_FORMAT_R32G32_SFLOAT),
    };
    BufferLayout layout = BufferLayout(attribs);


    
    // (!) This member function must be called in order to configure the vertex description which
    // eventually gets passed into the wider pipeline config.
    layout.SetVertexBufferDesc(&mVertexBindingDesc, &mVertexAttribsDesc);



    // Finally create the vertex buffer which handled the entire creation and mapping of memory
    // (in this case an array of vertices) into a conveniant place in GPU VRAM.
    mVertexBuffer = std::make_unique<Buffer>(
        mDevice, 
        SQUARE_VERTICES.size()*sizeof(float), 
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        (void*)SQUARE_VERTICES.data()
    );

    vkBindBufferMemory(mDevice->GetDevice(), mVertexBuffer->GetBuffer(), mVertexBuffer->GetBufferMemory(), 0);

}
}