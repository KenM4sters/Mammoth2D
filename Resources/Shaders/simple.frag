#version 450

layout(location = 0) out vec4 FragColor;
layout(location = 1) in vec2 vTexCoords;

layout(push_constant) uniform Push 
{
    mat4 modelMatrix;
    mat4 viewProjectionMatrix;
    vec2 texCoords[6];
} push;

layout(binding = 0) uniform sampler2D texSampler;

void main() 
{
    if(texture(texSampler, vTexCoords).r + texture(texSampler, vTexCoords).g + texture(texSampler, vTexCoords).b == 3.0)
        discard;
    FragColor = vec4(texture(texSampler, vTexCoords).rgb, 1.0);
}   