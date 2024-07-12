#version 450

layout(location = 0) out vec4 FragColor;
layout(location = 1) in vec2 vTexCoords;

layout(push_constant) uniform Push 
{
    mat4 modelMatrix;
    mat4 viewProjectionMatrix;
    int entId;
} push;

layout(binding = 0) uniform sampler2D texSampler;
layout(binding = 1) uniform sampler2D texSampler1;
layout(binding = 2) uniform sampler2D texSampler2;
layout(binding = 3) uniform sampler2D texSampler3;
layout(binding = 4) uniform sampler2D texSampler4;
layout(binding = 5) uniform sampler2D texSampler5;

void main() 
{
    vec4 tex;

    if(push.entId == 0) {tex = texture(texSampler, vTexCoords).rgba;}
    else if(push.entId == 1) {tex = texture(texSampler1, vTexCoords).rgba;}
    else if(push.entId == 2) {tex = texture(texSampler1, vTexCoords).rgba;}
    else if(push.entId == 3) {tex = texture(texSampler1, vTexCoords).rgba;}
    else if(push.entId == 4) {tex = texture(texSampler1, vTexCoords).rgba;}
    else if(push.entId == 5) {tex = texture(texSampler2, vTexCoords).rgba;}
    else if(push.entId == 6) {tex = texture(texSampler3, vTexCoords).rgba;}
    else if(push.entId == 7) {tex = texture(texSampler4, vTexCoords).rgba;}
    else if(push.entId == 8) {tex = texture(texSampler5, vTexCoords).rgba;}


    if(tex.a < 1.0)
        discard;
    FragColor = tex;
}   