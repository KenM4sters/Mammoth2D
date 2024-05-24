#version 450

layout(location = 0) out vec4 FragColor;

layout(push_constant) uniform Push 
{
    mat4 modelMatrix;
    vec3 color;
    mat4 viewProjectionMatrix;
} push;

layout(binding = 0) uniform UBO 
{
    vec3 color;
} ubo;


void main() 
{
    FragColor = vec4(ubo.color, 1.0);
}   