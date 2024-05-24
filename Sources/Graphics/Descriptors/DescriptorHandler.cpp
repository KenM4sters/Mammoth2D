#include "DescriptorHandler.hpp"

namespace Super 
{
DescriptorHandler::DescriptorHandler(DescriptorSet sets[1]) 
{
    mDescriptorSets.push_back(sets[0]);
}

DescriptorHandler::~DescriptorHandler() 
{

}

// void DescriptorHandler::AllocateDescriptorSet(DescriptorSet& descriptorSet) 
// {
//     mDescriptorSets.push_back(descriptorSet);
// }

}