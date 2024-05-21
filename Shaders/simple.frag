#version 450

layout(location = 0) out vec4 FragColor;

layout(push_constant) uniform Push 
{
    mat4 modelMatrix;
    vec3 color;
    mat4 viewProjectionMatrix;
} push;

void main() 
{
    FragColor = vec4(push.color, 1.0);
}   