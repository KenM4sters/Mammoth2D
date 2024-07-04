#include "Logging.hpp"

namespace mt 
{
    
void LOG_INT(int i, std::string name) 
{
    std::cout << name << " | " << i << std::endl;
}

void LOG_FLOAT(float f, std::string name) 
{
    std::cout << name << " | " << f << std::endl;

}

void LOG_VEC2(glm::vec2 v, std::string name) 
{
    std::cout << name << " | " << "x: " << v.x << "   " << "y: " << v.y << std::endl;
}

void LOG_VEC3(glm::vec3 v, std::string name) 
{
    std::cout << name << " | " << "x: " << v.x << "   " << "y: " << v.y << "   " << v.z << std::endl;
}


}