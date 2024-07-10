
## Ideas for the end-goal user api (pseudocode)

### 1. Heigh-level
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


### 4. Mid-level
```
int main() 
{

}

```


### 3. Low-level
```
int main() 
{

    const program = mt::createProgram("vert", "frag");
    

    shader.setShaderResource("modelMatrix", mt::ShaderResourceType::Mat4x4f, &modelMatrix);
    shader.setShaderResource("someMatrix", mt::ShaderResourceType::Mat4x4f, nullptr);
    
    shader.writeShaderResource("someMatrix", &someRandomMatrix);

    const cubeBuffer = mt::createVertexBuffer();

    while(!mt::windowShouldClose()) 
    {
        mt::setState(mt::DEPTH_TEST_LEQUAL, mt::CULL_MODE_OFF, mt::BLEND_ONE_TO_ONE);
        mt::clearColor(mt::COLOR_ORANGE);

        mt::begin();

        mt::setVertexBuffer(cubeVertexBuffer);
        mt::setIndexBuffer(cubeIndexBuffer);

        mt::submit();

        mt::end();

        mt::progress();
    }

}
```

