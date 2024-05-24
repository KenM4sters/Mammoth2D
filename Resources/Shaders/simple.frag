#version 450

layout(location = 0) out vec4 FragColor;
layout(location = 1) in vec2 vTexCoords;

layout(push_constant) uniform Push 
{
    mat4 modelMatrix;
    vec3 color;
    mat4 viewProjectionMatrix;
} push;

layout(binding = 0) uniform sampler2D texSampler;

void main() 
{
    FragColor = vec4(texture(texSampler, vTexCoords).rgb, 1.0);
}   