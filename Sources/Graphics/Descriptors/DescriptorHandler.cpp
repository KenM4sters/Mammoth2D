#include "DescriptorHandler.hpp"

namespace Super 
{
DescriptorHandler::DescriptorHandler(std::vector<DescriptorSet>& sets)
    : mDescriptorSets(sets)
{
}

DescriptorHandler::~DescriptorHandler() 
{

}

}