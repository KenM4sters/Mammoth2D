#pragma once
#include <glm/glm.hpp>
#include <iostream>

namespace Super 
{

void LOG_INT(int i, std::string name = "");
void LOG_FLOAT(float f, std::string name = "");
void LOG_VEC2(glm::vec2 v, std::string name = "");
void LOG_VEC3(glm::vec3 v, std::string name = "");

}