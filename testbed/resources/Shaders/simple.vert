#version 450

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexCoords;

layout(push_constant) uniform Push 
{
    mat4 modelMatrix;
    mat4 viewProjectionMatrix;
    int entId;
} push;

layout(location = 1) out vec2 vTexCoords;

void main() 
{
    vTexCoords = aTexCoords;
    gl_Position = push.viewProjectionMatrix * push.modelMatrix * vec4(aPosition, 0.0, 1.0);
}

