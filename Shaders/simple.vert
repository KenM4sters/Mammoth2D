#version 450

layout(location = 0) in vec2 aPosition;

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
    gl_Position = push.viewProjectionMatrix * push.transform.modelMatrix * vec4(aPosition, 0.0, 1.0);
}

