

#include "api.hpp"

#include <iostream>

namespace mt 
{

struct BufferView 
{
    size_t byteLength;
    size_t byteOffset;
};


struct BufferAccessor 
{
    BufferAccessor(BufferView* view, size_t byteLength)
        : byteLength{byteLength} 
    {

    }

    size_t byteOffset;
    size_t byteLength;
};

struct BufferLayout 
{
    BufferLayout(BufferAccessor* accessors, size_t byteSize)
        : accessors{accessors}, byteSize{byteSize} 
    {

        if(byteSize % sizeof(BufferAccessor) != 0) 
        {
            // TEMPORARY - trying not to throw errors.
            throw std::runtime_error("Failed to create BufferLayout: byteSize must be a multiple of the size of a BufferAccessor!");
        }

        size_t length = byteSize / sizeof(BufferAccessor);

        size_t stride = 0;
        for(size_t i = 0; i < length; i++) 
        {
            accessors[i].byteOffset = stride;
            stride += accessors[i].byteLength;
        }   
    }

    BufferAccessor* accessors;
    size_t byteSize;
};


}