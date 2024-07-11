

#include <glad/gl.h>

#include <iostream>
#include <vector>


namespace mt 
{

class GLBufferAttribute  
{
public:

    GLBufferAttribute(uint32_t shaderLoc, size_t byteSize) 
        : mShaderLoc{shaderLoc}, mByteSize{byteSize}
    {}

    [[nodiscard]] constexpr size_t GetSize() const noexcept { return mByteSize; }

    [[nodiscard]] constexpr uint32_t GetShaderLocation() const noexcept { return mShaderLoc; }

public:
    size_t mOffset = 0; // The unique, per attribute offset is set by the buffer layout, since it needs information about all attributes.

protected:
    size_t mByteSize = 0;
    uint32_t mShaderLoc = 0;
};

class GLBufferAccessor 
{
public:
    GLBufferAccessor(std::vector<GLBufferAttribute>& attribs)
        : mAttribs{attribs}, mStride{0}
    {
        CalculateStrideAndOffset();
    }

    [[nodiscard]] constexpr const size_t GetBufferStride() const noexcept { return mStride; }

    [[nodiscard]] constexpr const std::vector<GLBufferAttribute>& GetAttributes() const noexcept { return mAttribs; }

    void CalculateStrideAndOffset() 
    {
        for(auto& attrib : mAttribs) 
        {
            attrib.mOffset = mStride;
            mStride += attrib.GetSize();
        }
    }

private:
    std::vector<GLBufferAttribute>& mAttribs;
    size_t mStride;
};

}