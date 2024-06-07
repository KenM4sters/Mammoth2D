#ifndef MAMMOTH_2D_SUBRENDER_HPP
#define MAMMOTH_2D_SUBRENDER_HPP

#include "Pipeline.hpp"

namespace mt 
{
class Subrender 
{
public: 
    Subrender();
    ~Subrender();

private:
    std::unique_ptr<Pipeline> mPipeline = nullptr;

};
}

#endif