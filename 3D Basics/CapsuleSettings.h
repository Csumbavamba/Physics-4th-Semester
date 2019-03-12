#pragma once
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\common.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"


struct LineSegment
{
	glm::vec3 pointA = glm::vec3();
	glm::vec3 pointB = glm::vec3();

	LineSegment() {};

	LineSegment(glm::vec3 pointA, glm::vec3 pointB)
	{
		this->pointA = pointA;
		this->pointB = pointB;
	}
};

struct CapsuleSettings
{
	LineSegment lineSegment;
	float radius;

	CapsuleSettings() {};

	CapsuleSettings(LineSegment lineSegment, float radius)
	{
		this->lineSegment = lineSegment;
		this->radius = radius;
	}
};

