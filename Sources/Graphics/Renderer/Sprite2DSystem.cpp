#include "Sprite2DSystem.hpp"
#include "Graphics/Pipelines/VertexInput.hpp"
#include "Scene/Scene.hpp"
#include "Graphics/Pipelines/Shader.hpp"

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

    BufferLayout bufferLayout = BufferLayout(attribs);
    VertexInput vertexInput = VertexInput(bufferLayout);
    Uniform uniform = Uniform(0, sizeof(SimpleUniformBuffer), 0, VK_SHADER_STAGE_FRAGMENT_BIT);

    std::unique_ptr<Shader> shader = std::make_unique<Shader>(
        mDevice,    
        "Shaders/simple.vert.spv",
        "Shaders/simple.frag.spv",
        vertexInput,
        uniform
    );

    // Memory is deleted in the destructor of the base RenderSystem class.
    Pipeline* playerPipeline = new Pipeline(
        device, 
        renderPass,
        width,
        height,
        std::move(shader)
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

        // Uniforms and Descriptor sets.
        //
        SimpleUniformBuffer data{glm::vec3{0.0f, 0.0f, 1.0f}};
        std::vector<std::unique_ptr<UniformBuffer>> uniformBuffers(SwapChain::FRAMES_IN_FLIGHT);
        for(int i = 0; i < SwapChain::FRAMES_IN_FLIGHT; i++) 
        {
            auto buffer = std::make_unique<UniformBuffer>(mDevice, sizeof(SimpleUniformBuffer));
            buffer->Update((void*)&data);
            uniformBuffers.emplace_back(std::move(buffer));
        }

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
    
    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3(ent.tx.position, 0.0f));
    model = glm::scale(model, glm::vec3(ent.tx.scale, 1.0f));

    mPushConstants.modelMatrix = model;
    mPushConstants.color = ent.color;
    mPushConstants.projectionViewMatrix = Scene::GetCamera()->GetProjectionMatrix();
}

}