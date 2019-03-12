#pragma once
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\common.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"

#include "Triangle.h"
#include <math.h>
#include "CapsuleSettings.h"

enum PlaneState
{
	ONPLANE,
	BEHIND,
	INFRONT
};



class Physics
{
public:
	
	static Physics * GetInstance();
	static void ShutDown();
	
	static PlaneState IsPointOnPlane(glm::vec3 pointToCheck, glm::vec3 planeNormalVector, glm::vec3 pointOnPlane);
	static void ProveLagrangeValid(glm::vec3 vector1, glm::vec3 vector2, glm::vec3 vector3);
	static bool IsLineCollidingWithPlane(glm::vec3 linePoint1, glm::vec3 linePoint2, glm::vec3 planeNormal, glm::vec3 pointOnPlane);
	static bool IsTriangleCollidingWithPlane(Triangle triangle, glm::vec3 planeNormal, glm::vec3 pointOnPlane);
	
	// Capsule Collision
	float GetShortestDistanceBetweenLineSegments(LineSegment segment1, LineSegment segment2);
	float GetDistanceToSegment2D(glm::vec3 point, LineSegment segment);
	static bool IsCapsuleColliding(CapsuleSettings capsule1, CapsuleSettings capsule2);

private:
	Physics() {};
	~Physics() {};
	Physics(const Physics& copy) {};
	Physics& operator= (const Physics& move) {};

	static Physics * instance;
};

