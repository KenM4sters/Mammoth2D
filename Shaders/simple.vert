#version 450

layout(location = 0) in vec2 aPosition;
layout(push_constant) uniform Push 
{
    mat4 modelMatrix;
    vec3 color;
    mat4 viewProjectionMatrix;
} push;


void main() 
{
    gl_Position = push.viewProjectionMatrix * push.modelMatrix * vec4(aPosition, 0.0, 1.0);
}

