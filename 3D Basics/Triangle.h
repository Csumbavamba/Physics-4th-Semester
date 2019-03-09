#pragma once

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\common.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"

struct Triangle
{
	glm::vec3 pointA = glm::vec3();
	glm::vec3 pointB = glm::vec3();
	glm::vec3 pointC = glm::vec3();

	Triangle() {};

	Triangle(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC)
	{
		this->pointA = pointA;
		this->pointB = pointB;
		this->pointC = pointC;
	}
};

