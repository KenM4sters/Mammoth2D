#ifndef MAMMOTH_2D_LOGGING_HPP
#define MAMMOTH_2D_LOGGING_HPP

#include <glm/glm.hpp>

#include <iostream>

namespace mt 
{
void LOG_INT(int i, std::string name = "");
void LOG_FLOAT(float f, std::string name = "");
void LOG_VEC2(glm::vec2 v, std::string name = "");
void LOG_VEC3(glm::vec3 v, std::string name = "");

}

#endif