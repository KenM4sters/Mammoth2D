#version 450

layout(location = 0) out vec4 FragColor;

struct Transform 
{
    vec2 position;
    vec2 scale;
    mat4 modelMatrix;
};

layout(push_constant) uniform Push 
{
    Transform transform;
    vec3 color;
    mat4 viewProjectionMatrix;
} push;

void main() 
{
    FragColor = vec4(push.color, 1.0);
}   