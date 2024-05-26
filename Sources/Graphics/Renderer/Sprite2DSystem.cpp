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
    // Texture Coordinates
    //
    glm::vec2 texCoordsPlayer[6] = 
    {
        glm::vec2(0.32f, 0.65f), 
        glm::vec2(0.34f, 0.71f), 
        glm::vec2(0.32f, 0.71f),

        glm::vec2(0.32f, 0.65f), 
        glm::vec2(0.34f, 0.65f), 
        glm::vec2(0.34f, 0.71f)
    };

    glm::vec2 texCoordsEnemy[6] = 
    {
        glm::vec2(0.32f, 0.65f), 
        glm::vec2(0.34f, 0.71f), 
        glm::vec2(0.32f, 0.71f),

        glm::vec2(0.32f, 0.65f), 
        glm::vec2(0.34f, 0.65f), 
        glm::vec2(0.34f, 0.71f)
    };

    glm::vec2 texCoordsBackground[6] = 
    {
        glm::vec2(0.0f, 0.05f), 
        glm::vec2(0.76f, 0.56f), 
        glm::vec2(0.0f, 0.56f),

        glm::vec2(0.0f, 0.05f), 
        glm::vec2(0.76f, 0.05f), 
        glm::vec2(0.76f, 0.56f)
    };

    glm::vec2 texCoordsPlatform1[6] = 
    {
        glm::vec2(0.12f, 0.7f), 
        glm::vec2(0.14f, 0.76f), 
        glm::vec2(0.12f, 0.76f),

        glm::vec2(0.12f, 0.7f), 
        glm::vec2(0.14f, 0.7f), 
        glm::vec2(0.14f, 0.76f)
    };

    glm::vec2 texCoordsPlatform2[6] = 
    {
        glm::vec2(0.32f, 0.68f), 
        glm::vec2(0.34f, 0.73f), 
        glm::vec2(0.32f, 0.73f),

        glm::vec2(0.32f, 0.68f), 
        glm::vec2(0.34f, 0.68f), 
        glm::vec2(0.34f, 0.73f)
    };

    glm::vec2 texCoordsPlatform3[6] = 
    {
        glm::vec2(0.72f, 0.5f), 
        glm::vec2(1.0f, 1.0f), 
        glm::vec2(0.72f, 1.0f),

        glm::vec2(0.72f, 0.5f), 
        glm::vec2(1.0f, 0.5f), 
        glm::vec2(1.0f, 1.0f)
    };

    for(int i = 0; i < 6; i++) 
    {
        mTexCoords[0][i] = texCoordsPlayer[i];
        mTexCoords[1][i] = texCoordsEnemy[i];
        mTexCoords[2][i] = texCoordsPlatform1[i];
        mTexCoords[3][i] = texCoordsPlatform2[i];
        mTexCoords[4][i] = texCoordsPlatform3[i];
        mTexCoords[5][i] = texCoordsBackground[i];
    }


    std::array<std::unique_ptr<Image>, 6> images = 
    {
        std::make_unique<Image>(mDevice, "Resources/Textures/Player.png"),
        std::make_unique<Image>(mDevice, "Resources/Textures/Box.png"),
        std::make_unique<Image>(mDevice, "Resources/Textures/Platform.png"),
        std::make_unique<Image>(mDevice, "Resources/Textures/Platform.png"),
        std::make_unique<Image>(mDevice, "Resources/Textures/Platform.png"),
        std::make_unique<Image>(mDevice, "Resources/Textures/Background.png"),
    };

    mPipelines = std::make_unique<std::unordered_map<std::string, Pipeline*>>();

    std::vector<BufferAttribute> attribs = 
    {
        BufferAttribute(0, VK_FORMAT_R32G32_SFLOAT),
        BufferAttribute(1, VK_FORMAT_R32G32_SFLOAT),
    };

    TexturePushConstant pushConstantData;

    memcpy(pushConstantData.texCoords, texCoordsBackground, 6*sizeof(glm::vec2));

    BufferLayout bufferLayout = BufferLayout(attribs);
    VertexInput vertexInput = VertexInput(bufferLayout);
    Constant pushConstant = Constant(pushConstantData, sizeof(TexturePushConstant), 0, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT);
    Uniform uniform = Uniform(0, sizeof(SimpleUniformBuffer), 0, VK_SHADER_STAGE_FRAGMENT_BIT);

    std::unique_ptr<Shader> shader = std::make_unique<Shader>(
        mDevice,    
        "Resources/Shaders/simple.vert.spv",
        "Resources/Shaders/simple.frag.spv",
        vertexInput,
        pushConstant,
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

    std::vector<DescriptorSet> sets{};
    for(int i = 0; i < images.size(); i++) 
    {
        sets.push_back(DescriptorSet(mDevice, playerPipeline, i));     
    }
    
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
    for(int i = 0; i < images.size(); i++) 
    {
        auto& imageInfo = images[i]->GetUniformBuffer()->GetDescriptorImageInfo();
        auto& descriptorSet = mDescriptorHandler->GetDescriptorSet(i);
        mDescriptorWriter->WriteToBuffer(i, i, imageInfo, descriptorSet);
    }
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
        mDescriptorHandler->GetDescriptorSet(ent.id).Bind(commandBuffer);
        
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
            sizeof(TexturePushConstant), 
            pipeline->GetShader()->GetPushConstant().GetData()
        );

        // Finally Draw.
        //
        vkCmdDraw(commandBuffer, 6, 1, 0, 0);
    }
}

void Sprite2DSystem::UpdatePushConstants(Entity& ent) 
{
    const auto& pipeline = mPipelines->operator[]("playerPipeline");
    const auto& pushData = pipeline->GetShader()->GetPushConstant().GetData();

    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3(ent.tx.position, 0.0f));
    model = glm::scale(model, glm::vec3(ent.tx.scale, 1.0f));

    pushData->modelMatrix = model;
    pushData->projectionViewMatrix = Scene::GetCamera()->GetProjectionMatrix();
    memcpy(pushData->texCoords, mTexCoords[ent.id], 6*sizeof(glm::vec2));
}

}