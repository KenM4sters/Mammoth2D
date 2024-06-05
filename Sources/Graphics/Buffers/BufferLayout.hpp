#ifndef MAMMOTH_2D_BUFFER_LAYOUT_HPP
#define MAMMOTH_2D_BUFFER_LAYOUT_HPP

#include <vulkan/vulkan.hpp>
#include "Device.hpp"

#include <vector>
#include <cassert>
#include <stdexcept>
#include <iostream>

namespace mt 
{
void SetVertexBufferFromVertices(Device& device, VkBuffer& buffer, VkDeviceMemory& deviceMemory, const std::vector<float>& vertices);

uint32_t FindSutiableMemoryType(uint32_t typeFilter, VkPhysicalDeviceMemoryProperties* memProperties, VkMemoryPropertyFlags properties);

extern std::vector<float> SQUARE_VERTICES;

class BufferAttribute  
{
    public:

        BufferAttribute(uint32_t shaderLoc, VkFormat format = VK_FORMAT_R32G32_SFLOAT) 
            : mShaderLoc{shaderLoc}, mFormat{format}
        {
            switch(format) 
            {
                case VK_FORMAT_R32G32_SFLOAT: mSize = 2*4; break;
                case VK_FORMAT_R32G32B32_SFLOAT: mSize = 3*4; break;
                default: mSize = 2*4; break;
            }
        }
        ~BufferAttribute() {}

        inline const VkFormat GetFormat() const { return mFormat; }
        inline const uint32_t GetSize() const { return mSize; }
        inline const uint32_t GetShaderLocation() const { return mShaderLoc; }

        uint32_t mOffset = 0; // The unique, per attribute offset is set by the buffer layout, since it needs information about all attributes.

    private:

        uint32_t mSize = 0;
        uint32_t mShaderLoc = 0;
        VkFormat mFormat;
};

class BufferLayout 
{
    public:

        BufferLayout(std::vector<BufferAttribute>& attribs)
            : mAttribs{attribs} 
        {
            CalculateStrideAndOffset();
        }

        ~BufferLayout() {}

        inline const uint32_t GetBufferStride() const { return mStride;}
        inline const std::vector<BufferAttribute>& GetAttributes() const { return mAttribs; }

        void CalculateStrideAndOffset() 
        {
            for(auto& attrib : mAttribs) 
            {
                attrib.mOffset = mStride;
                mStride += attrib.GetSize();
            }
        }

        const void SetVertexBufferDesc(VkVertexInputBindingDescription* bindingDesc, std::vector<VkVertexInputAttributeDescription>* attribsDesc) const 
        {   
            bindingDesc->binding = 0;
            bindingDesc->inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            bindingDesc->stride = mStride;

            for(int i = 0; i < mAttribs.size(); i++) 
            {
                VkVertexInputAttributeDescription attribDesc;
                attribDesc.binding = i;
                attribDesc.format = mAttribs[i].GetFormat();
                attribDesc.offset = mAttribs[i].mOffset;
                attribDesc.location = mAttribs[i].GetShaderLocation();

                attribsDesc->push_back(attribDesc);
            }
        }
    
    private:

        std::vector<BufferAttribute>& mAttribs;
        uint32_t mStride = 0;
};
}

#endif
