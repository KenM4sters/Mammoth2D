
#include "api.hpp"

#include <iostream>
#include <vector>

namespace mt 
{

class Mesh final 
{
public:
    explicit Mesh();
    ~Mesh() {}

    template<typename T>
    void AddShaderResource() noexcept 
    {

    }

    template<typename T, typename...Args>
    void AddShaderResource(const Args&... args) noexcept 
    {

    }


    void WriteShaderResource(const char* name, void* data, size_t byteSize) noexcept 
    {
        
    }

private:
    
};

}