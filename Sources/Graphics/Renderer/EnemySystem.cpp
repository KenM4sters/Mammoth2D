#include <glm/gtc/matrix_transform.hpp>
#include "EnemySystem.hpp"
#include "Scene/EntityManager.hpp"
#include "Graphics/Buffers/BufferLayout.hpp"
#include "Scene/Scene.hpp"


namespace Super
{

EnemySystem::EnemySystem(Device& device, VkRenderPass renderPass, uint32_t height, uint32_t width)
    : RenderSystem(device, renderPass, width, height)
{
    CreateEnemyEntity();
    CreatePipelineLayout();
    CreatePipeline(width, height, renderPass);
}

void EnemySystem::CreatePipelineLayout() 
{
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(SimplePushConstants);

 
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
    
    if(vkCreatePipelineLayout(mDevice.GetDevice(), &pipelineLayoutInfo, nullptr, &mPipelineLayout) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create pipeline layout!");
    }
}

void EnemySystem::CreatePipeline(uint32_t width, uint32_t height, VkRenderPass renderPass) 
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

void EnemySystem::UpdateBuffers() 
{
    
}

void EnemySystem::Run(VkCommandBuffer commandBuffer, std::vector<Entity>& entities) 
{
    mPipeline->Bind(commandBuffer);

    VkBuffer buffers[] = {mVertexBuffer->GetBuffer()};
    VkDeviceSize offsets[] = {0};

    vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);

    UpdatePushConstants(entities[1]);

    vkCmdPushConstants(
        commandBuffer, 
        mPipelineLayout, 
        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 
        0, 
        sizeof(SimplePushConstants), 
        &mPushConstants
    );
    
    vkCmdDraw(commandBuffer, 6, 1, 0, 0);
}

void EnemySystem::CreateEnemyEntity() 
{

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

    vkBindBufferMemory(mDevice.GetDevice(), mVertexBuffer->GetBuffer(), mVertexBuffer->GetBufferMemory(), 0);

}

void EnemySystem::UpdatePushConstants(Entity& enemy) 
{
    enemy.transform.modelMatrix = glm::mat4(1.0f);
    enemy.transform.modelMatrix = glm::translate(enemy.transform.modelMatrix, glm::vec3(enemy.transform.position, 0.0f));
    enemy.transform.modelMatrix = glm::scale(enemy.transform.modelMatrix, glm::vec3(enemy.transform.scale, 1.0f));

    mPushConstants.color = enemy.color;
    mPushConstants.transform.position = enemy.transform.position;
    mPushConstants.transform.scale = enemy.transform.scale;
    mPushConstants.transform.modelMatrix = enemy.transform.modelMatrix;

    mPushConstants.projectionViewMatrix = Scene::GetCamera()->GetProjectionMatrix();
}


}