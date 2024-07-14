
## Overview

### Requirements
- Must provide a concise, simple user api of functions only (I don't want users to 
create instances of objects themselves)
- Must be within a single namespace (e.g: mt::function, not mt::graphics::function)  
- Must provide a very high degree of flexibility that allows the users to interact with the backend api at a low level through the use of custom flags (e.g: sampling address modes, storage/usage specifiers etc)

### Record of caviets discovered through this project
- Given that this is an Object-Oriented framework, I wanted functions to return instances that 
the user could call methods on (not access members though), such as update(), destroy(), add() etc... This does raise the issue though of not being able to soley use unique_ptrs since polymoprhic behaviour is forbidden with those (other classes need to able to cast these pointers to different types for each graphics api), leaving the choice of either shared_ptrs or raw pointers. 


## Ideas for the end-goal user api (pseudocode)

### 1. High-level
```
int main() 
{
    const ShaderBlueprint shader = mt::ShaderBlueprint;
    shader.vertCode = mt::File::ParseShaderfile(".vs");
    shader.fragCode = mt::File::ParseShaderfile(".fs");
    shader.attributes = [
        mt::Attribute::Position,
        mt::Attribute::Normal,
        mt::Attribute::TexCoords1
    ];
    shader.uniforms = [
        {"randomInt", mt::UniformFormat::Int, 25},
        {"randomFloat", mt::UniformFormat::Float, 100.0f},
        {"projectionMatrix", mt::UniformFormat::Mat4x4f, nullptr},
        {"KenMasters", mt::UniformFormat::Sampler, mt::Factory::BuildTexture(".png")},
    ];

    shader.WriteUniform("projectionMatrix", camera.projectionMatrix);

    const MeshBlueprint mbp = mt::MeshBlueprint;
    mpb.shader = shader;
    mpb.vertices = mt::Primitve::Vertices::Cube;
    mpb.layout = mat::Primtive::Layout::PositionNormalTexCoords;

    const mesh = mt::Factory::BuildMesh(mbp);
}
```


### 2. Mid-level (mostly functional but some OOP)
```
int main() 
{
    mt::Window window = mt::createWindow("Example", 800, 600);

    mt::Application app;
    state.pWindow = &window;
    mt::init(app);


    const mt::Program& program = mt::createProgram("vert.sc", "frag.sc");

    const mt::Uniform& uModel = mt::createUniform("uModel",mt::ShaderResourceType::Mat4x4, nullptr);

    const mt::Shader& shader = mt::createShader();
    shader.setProgram(program);
    shader.addUniform(uModel);

    const mt::VertexBuffer& cubeBuffer = mt::createVertexBuffer();
    cubeBuffer.writeVertices(vertices);
    cubeBuffer.writeIndices(indices);
    cubeBuffer.setLayout(layout);
    
    const sceneFlags = MT_TEXTURE_COLOR_ATTACHMENT | MT_TEXTURE_S_CLAMP_TO_EDGE
        | MT_TEXTURE_U_CLAMP_TO_EDGE

    const sceneBuffer = mt::createFramebuffer(
        800,
        600,
        mt::TextureFormat::RGBA32F,
        sceneFlags
    );

    while(!mt::windowShouldClose()) 
    {
        mt::setState(mt::DEPTH_TEST_LEQUAL, mt::CULL_MODE_OFF, mt::BLEND_ONE_TO_ONE);
        mt::clearColor(mt::COLOR_ORANGE);

        uModel.write(&model);

        mt::begin(sceneBuffer);
        mt::submit(cubeBuffer, shader);
        mt::end();

        mt::begin(MT_SCREEN_BUFFER);
        mt::submit(cubeBuffer, shader);
        mt::end();

        mt::progress(); // progresses to the next frame.
    }

}
```


### 3. low-level (functional).
```
int main() 
{
    mt::initWindow("Example", 800, 600);

    const mt::ProgramHandle program = mt::createProgram("vert.sc", "frag.sc");

    const mt::UniformHandle uModel = mt::createUniform("uModel",mt::ShaderResourceType::Mat4x4, nullptr);

    const mt::ShaderHandle shader = mt::createShader(program, [uModel, uView]);

    const cubeBuffer = mt::createVertexBuffer(cubeVertices, cubeIndices, layout);
    
    const sceneFlags = MT_TEXTURE_COLOR_ATTACHMENT | MT_TEXTURE_S_CLAMP_TO_EDGE
        | MT_TEXTURE_U_CLAMP_TO_EDGE

    const sceneBuffer = mt::createFramebuffer(
        800,
        600,
        mt::TextureFormat::RGBA32F,
        sceneFlags
    );

    while(!mt::windowShouldClose()) 
    {
        mt::setState(mt::DEPTH_TEST_LEQUAL, mt::CULL_MODE_OFF, mt::BLEND_ONE_TO_ONE);
        mt::clearColor(mt::COLOR_ORANGE);

        mt::writeUniform("uModel", &model);

        mt::begin(sceneBuffer);
        mt::submit(cubeBuffer, shader);
        mt::end();

        mt::begin(MT_SCREEN_BUFFER);
        mt::submit(cubeBuffer, shader);
        mt::end();

        mt::progress(); // progresses to the next frame.
    }
}

```


