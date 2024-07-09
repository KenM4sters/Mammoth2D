```


int main() 
{

    const shader = mt::ShaderBlueprint;
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

    const mbp = mt::MeshBlueprint;
    mpb.shader = shader;
    mpb.vertices = mt::Primitve::Vertices::Cube;
    mpb.layout = mat::Primtive::Layout::PositionNormalTexCoords;

    const mesh = mt::Factory::BuildMesh(mbp);
}



```