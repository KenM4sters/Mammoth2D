#include "DescriptorHandler.hpp"

namespace Super 
{
DescriptorHandler::DescriptorHandler(DescriptorSet sets[2]) 
{
    mDescriptorSets.push_back(sets[0]);
    mDescriptorSets.push_back(sets[1]);
}

DescriptorHandler::~DescriptorHandler() 
{

}

// void DescriptorHandler::AllocateDescriptorSet(DescriptorSet& descriptorSet) 
// {
//     mDescriptorSets.push_back(descriptorSet);
// }

}