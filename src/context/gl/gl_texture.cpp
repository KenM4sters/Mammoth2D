#include "gl_texture.hpp"

//================================================================
// 2D impl
//================================================================

GLTexture2D::GLTexture2D(GLTextureBlueprint blueprint) 
    : mBlueprint{blueprint}
{
    glGenTextures(1, &mProgram);
    glBindTexture(GL_TEXTURE_2D, mProgram);
    
    glSamplerParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mBlueprint.samplerBlueprint.minFilter);
    glSamplerParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mBlueprint.samplerBlueprint.magFilter);
    glSamplerParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mBlueprint.samplerBlueprint.sWrap);
    glSamplerParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mBlueprint.samplerBlueprint.tWrap);
    glSamplerParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, mBlueprint.samplerBlueprint.rWrap);

    glTexImage2D(GL_TEXTURE_2D, 0, mBlueprint.format, mBlueprint.width, mBlueprint.height, 0, mBlueprint.nChannels, mBlueprint.type, mBlueprint.data);

    if(mBlueprint.generateMipMaps) 
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void GLTexture2D::Resize(const uint32_t width, const uint32_t height) 
{
    mBlueprint.width = width;
    mBlueprint.height = height;

    glBindTexture(GL_TEXTURE_2D, mProgram);
    glTexImage2D(GL_TEXTURE_2D, 0, mBlueprint.format, mBlueprint.width, mBlueprint.height, 0, mBlueprint.nChannels, mBlueprint.type, mBlueprint.data);

    if(mBlueprint.generateMipMaps) 
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void GLTexture2D::Destroy() 
{
    glDeleteTextures(1, &mProgram);
}



//================================================================
// Cube impl
//================================================================

GLTextureCube::GLTextureCube(GLTextureBlueprint blueprint) 
    : mBlueprint{blueprint}
{
    glGenTextures(1, &mProgram);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mProgram);
    
    glSamplerParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, mBlueprint.samplerBlueprint.minFilter);
    glSamplerParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mBlueprint.samplerBlueprint.magFilter);
    glSamplerParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, mBlueprint.samplerBlueprint.sWrap);
    glSamplerParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, mBlueprint.samplerBlueprint.tWrap);
    glSamplerParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, mBlueprint.samplerBlueprint.rWrap);

    for(int i = 0; i < 6; i++) 
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, mBlueprint.format, mBlueprint.width, mBlueprint.height, 0, mBlueprint.nChannels, mBlueprint.type, mBlueprint.data);
    }

    if(mBlueprint.generateMipMaps) 
    {
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, GL_NONE);
}

void GLTextureCube::Resize(const uint32_t width, const uint32_t height) 
{
    mBlueprint.width = width;
    mBlueprint.height = height;

    glBindTexture(GL_TEXTURE_CUBE_MAP, mProgram);
    glTexImage2D(GL_TEXTURE_CUBE_MAP, 0, mBlueprint.format, mBlueprint.width, mBlueprint.height, 0, mBlueprint.nChannels, mBlueprint.type, mBlueprint.data);

    if(mBlueprint.generateMipMaps) 
    {
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }
}

void GLTextureCube::Destroy() 
{
    glDeleteTextures(1, &mProgram);
}