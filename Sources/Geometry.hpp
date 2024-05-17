#pragma once
#include <iostream>
#include <vector>


class Geometry 
{
    public:

        Geometry(const std::shared_ptr<Device>& device);

        ~Geometry();

        inline const NativeBufferLayout& GetNativeBufferLayout() const { return mNativeLayout; }

        inline const WGPUBuffer& GetVertexBuffer() const { return mVertexBuffer; }

        inline const std::vector<float>& GetVertices() const { return mVertices; }

    private:
    
        void CreateBuffers(const std::shared_ptr<Device>& device);

        std::vector<float>& mVertices;

        std::shared_ptr<BufferLayout> mBufferLayout = nullptr;

        WGPUBuffer mVertexBuffer = nullptr;

        NativeBufferLayout mNativeLayout{};

};