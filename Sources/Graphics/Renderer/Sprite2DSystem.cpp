#include "Sprite2DSystem.hpp"
#include "Graphics/Pipelines/VertexInput.hpp"
#include "Scene/Scene.hpp"
#include "Graphics/Pipelines/Shader.hpp"
#include "Logging.hpp"

namespace Super 
{
Sprite2DSystem::Sprite2DSystem(Device& device, VkRenderPass renderPass, uint32_t width, uint32_t height)
    : RenderSystem(device, renderPass, width, height)
{
    mPipelines = std::make_unique<std::unordered_map<std::string, Pipeline*>>();

    mImage = std::make_unique<Image>(mDevice, "Resources/Textures/Atlas.png");

    std::vector<BufferAttribute> attribs = 
    {
        BufferAttribute(0, VK_FORMAT_R32G32_SFLOAT),
        BufferAttribute(1, VK_FORMAT_R32G32_SFLOAT),
    };

    BufferLayout bufferLayout = BufferLayout(attribs);
    VertexInput vertexInput = VertexInput(bufferLayout);
    Uniform uniform = Uniform(0, sizeof(SimpleUniformBuffer), 0, VK_SHADER_STAGE_FRAGMENT_BIT);

    std::unique_ptr<Shader> shader = std::make_unique<Shader>(
        mDevice,    
        "Resources/Shaders/simple.vert.spv",
        "Resources/Shaders/simple.frag.spv",
        vertexInput,
        uniform
    );


    // Pipeline
    //
    // Memory is deleted in the destructor of the base RenderSystem class.
    Pipeline* playerPipeline = new Pipeline(
        device, 
        renderPass,
        width,
        height,
        std::move(shader),
        VK_PIPELINE_BIND_POINT_GRAPHICS
    );

    // At the moment, all pipelines are the same, since we're only rendering simple squares,
    // but eventually this will change.
    //
    mPipelines->operator[]("playerPipeline") = playerPipeline;

    auto descriptorSetA = DescriptorSet(mDevice, playerPipeline);     

    DescriptorSet sets[1] = {descriptorSetA};

    mDescriptorHandler = std::make_unique<DescriptorHandler>(sets);

    mDescriptorWriter = std::make_unique<DescriptorWriter>();

    // Create the vertex buffer which handled the entire creation and mapping of memory
    // (in this case an array of vertices) into a conveniant place in GPU VRAM.
    mVertexBuffer = std::make_unique<Buffer>(
        mDevice, 
        PLAYER_VERTICES.size()*sizeof(float), 
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        (void*)PLAYER_VERTICES.data()
    );

    vkBindBufferMemory(mDevice.GetDevice(), mVertexBuffer->GetBuffer(), mVertexBuffer->GetBufferMemory(), 0);


    // Uniform image buffer
    //
    auto& imageInfo = mImage->GetUniformBuffer()->GetDescriptorImageInfo();
    auto& descriptorSet = mDescriptorHandler->GetDescriptorSet(0);
    mDescriptorWriter->WriteToBuffer(0, imageInfo, descriptorSet);
    mDescriptorWriter->UpdateDescriptorSet(mDevice);
    
}

Sprite2DSystem::~Sprite2DSystem() 
{

}

void Sprite2DSystem::Run(VkCommandBuffer commandBuffer, int frameIndex, std::vector<Entity>& entities) 
{
    SimpleUniformBuffer data[3] = 
    {
        glm::vec3{1.0f, 0.0f, 1.0f},
        glm::vec3{0.0f, 0.0f, 1.0f},
        glm::vec3{1.0f, 0.0f, 0.0f}
    };

    for(auto& ent : entities) 
    {
        // Pipeline.
        //
        const auto& pipeline = mPipelines->operator[]("playerPipeline");
        pipeline->Bind(commandBuffer);

        // Uniforms and Descriptor sets.
        //
        mDescriptorHandler->GetDescriptorSet(0).Bind(commandBuffer);
        
        // Vertex Buffers.
        //
        VkBuffer buffers[] = {mVertexBuffer->GetBuffer()};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);

        // Push constants.
        //
        UpdatePushConstants(ent);
        vkCmdPushConstants(
            commandBuffer, 
            pipeline->GetPipelineLayout(), 
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 
            0, 
            sizeof(SimplePushConstants), 
            &mPushConstants
        );

        // Finally Draw.
        //
        vkCmdDraw(commandBuffer, 6, 1, 0, 0);
    }
}

void Sprite2DSystem::UpdatePushConstants(Entity& ent) 
{
    
    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3(ent.tx.position, 0.0f));
    model = glm::scale(model, glm::vec3(ent.tx.scale, 1.0f));

    mPushConstants.modelMatrix = model;
    mPushConstants.color = ent.color;
    mPushConstants.projectionViewMatrix = Scene::GetCamera()->GetProjectionMatrix();
}

}