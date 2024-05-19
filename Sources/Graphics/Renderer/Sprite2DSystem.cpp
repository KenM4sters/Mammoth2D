#include "Sprite2DSystem.hpp"
#include "Graphics/Pipelines/VertexInput.hpp"
#include "Scene/Scene.hpp"

namespace Super 
{
Sprite2DSystem::Sprite2DSystem(Device& device, VkRenderPass renderPass, uint32_t width, uint32_t height)
    : RenderSystem(device, renderPass, width, height)
{
    mPipelines = std::make_unique<std::unordered_map<std::string, Pipeline*>>();

    std::vector<BufferAttribute> attribs = 
    {
        BufferAttribute(0, VK_FORMAT_R32G32_SFLOAT),
    };

    auto bufferLayout = std::make_unique<BufferLayout>(attribs);

    VertexInput vertexInput = VertexInput(std::move(bufferLayout));

    // Memory is deleted in the destructor of the base class.
    Pipeline* playerPipeline = new Pipeline(
        device, 
        renderPass,
        std::move(vertexInput),
        "Shaders/simple.vert.spv", 
        "Shaders/simple.frag.spv",
        width,
        height
    );

    // At the moment, all pipelines are the same, since we're only rendering simple squares,
    // but eventually this will change.
    //
    mPipelines->operator[]("playerPipeline") = playerPipeline;


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

Sprite2DSystem::~Sprite2DSystem() 
{

}

void Sprite2DSystem::Run(VkCommandBuffer commandBuffer, std::vector<Entity>& entities) 
{
    for(auto& ent : entities) 
    {
        const auto& pipeline = mPipelines->operator[]("playerPipeline");

        pipeline->Bind(commandBuffer);
        
        VkBuffer buffers[] = {mVertexBuffer->GetBuffer()};
        VkDeviceSize offsets[] = {0};

        vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);

        UpdatePushConstants(ent);

        vkCmdPushConstants(
            commandBuffer, 
            pipeline->GetPipelineLayout(), 
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 
            0, 
            sizeof(SimplePushConstants), 
            &mPushConstants
        );
        
        vkCmdDraw(commandBuffer, 6, 1, 0, 0);
    }
}

void Sprite2DSystem::UpdatePushConstants(Entity& ent) 
{
    mPushConstants.color = ent.color;
    mPushConstants.transform.position = ent.transform.position;
    mPushConstants.transform.scale = ent.transform.scale;
    mPushConstants.transform.modelMatrix = ent.transform.modelMatrix;

    mPushConstants.projectionViewMatrix = Scene::GetCamera()->GetProjectionMatrix();
}

}