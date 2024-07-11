

#include "api.hpp"


class VertexBuffer 
{
public:
    virtual ~VertexBuffer() {}
    virtual void create(const void* const data, const size_t byteSize) = 0;
    virtual void destroy() = 0;
    virtual void update(const size_t offset, const void* const data, const size_t byteSize) = 0;
};

class IndexBuffer 
{
public:
    virtual ~IndexBuffer() {}
    virtual void create(const void* const data, const size_t byteSize) = 0;
    virtual void destroy() = 0;
    virtual void update(const size_t offset, const void* const data, const size_t byteSize) = 0;
};

class UniformBuffer 
{
public:
    virtual ~UniformBuffer() {}
    virtual void create(const void* const data, const size_t byteSize) = 0;
    virtual void destroy() = 0;
    virtual void update(const size_t offset, const void* const data, const size_t byteSize) = 0;
};

class Program 
{
public:
    virtual ~Program() {}
    virtual void create(const char* vertPath, const char* fragPath) = 0;
    virtual void destroy() = 0;
};

class Texture 
{
public:
    virtual ~Texture() {}
    virtual void create();
};


class IRenderer 
{
    virtual ~IRenderer() {}

    virtual void createVertexBuffer() = 0;
};