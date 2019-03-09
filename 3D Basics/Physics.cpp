#include "Physics.h"
#include <iostream>

Physics * Physics::instance = NULL;

Physics * Physics::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Physics();
	}
	return instance;
}

PlaneState Physics::IsPointOnPlane(glm::vec3 pointToCheck, glm::vec3 planeNormalVector, glm::vec3 pointOnPlane)
{
	// Print given details
	std::cout << "Checking whether point wiht coordinates of: "
		<< pointToCheck.x
		<< ", " << pointToCheck.y
		<< ", " << pointToCheck.z
		<< " is on the plane, with the normal vector of "
		<< planeNormalVector.x
		<< ", " << planeNormalVector.y
		<< ", " << planeNormalVector.z << std::endl << std::endl;

	// See if it's on the plane
	if (glm::dot((pointToCheck - pointOnPlane), planeNormalVector) == 0)
	{
		std::cout << "it is on the plane" << std::endl << std::endl;;
		return PlaneState::ONPLANE;
	}
	else
	{
		// TODO Check if behind or not

		std::cout << "It is not on the plane" << std::endl << std::endl;;
		return PlaneState::BEHIND; // TODO Remove after implementing
	}
}

void Physics::ProveLagrangeValid(glm::vec3 vector1, glm::vec3 vector2, glm::vec3 vector3)
{
	// If the result is the same it's valid, otherwise it is not
	if (glm::dot(vector1, glm::cross(vector2, vector3)) == glm::dot(vector2, glm::cross(vector1, vector3)))
	{
		std::cout << "Lagrange formula is valid." << std::endl << std::endl;
	}
	else
	{
		std::cout << "Lagrange formula is not valid." << std::endl << std::endl;
	}
}

bool Physics::IsLineCollidingWithPlane(glm::vec3 linePoint1, glm::vec3 linePoint2, glm::vec3 planeNormal, glm::vec3 pointOnPlane)
{
	// Print given details
	std::cout << "Checking whether Line Segment with Points of: "
		<< linePoint1.x
		<< ", " << linePoint1.y
		<< ", " << linePoint1.z
		<< "and :"
		<< linePoint2.x
		<< ", " << linePoint2.y
		<< ", " << linePoint2.z
		<< " is colliding with a plane that has the normal vector of "
		<< planeNormal.x
		<< ", " << planeNormal.y
		<< ", " << planeNormal.z 
		<< " and the point of: "
		<< pointOnPlane.x
		<< ", " << pointOnPlane.y
		<< ", " << pointOnPlane.z
		<< std::endl << std::endl;

	// Either one of the points on the line are on the plane
	if (IsPointOnPlane(linePoint1, planeNormal, pointOnPlane) == PlaneState::ONPLANE || 
		IsPointOnPlane(linePoint2, planeNormal, pointOnPlane) == PlaneState::ONPLANE)
	{
		std::cout << "Colliding." << std::endl;
		return true;
	}
	// the line intersects the plane --> One is behind the other one is in front
	else if ((IsPointOnPlane(linePoint1, planeNormal, pointOnPlane) == PlaneState::INFRONT &&
		IsPointOnPlane(linePoint2, planeNormal, pointOnPlane) == PlaneState::BEHIND) ||
		(IsPointOnPlane(linePoint1, planeNormal, pointOnPlane) == PlaneState::BEHIND &&
			IsPointOnPlane(linePoint2, planeNormal, pointOnPlane) == PlaneState::INFRONT))
	{
		std::cout << "Colliding." << std::endl;
		return true;
	}

	std::cout << "Not Colliding." << std::endl;
	return false;
}

bool Physics::IsTriangleCollidingWithPlane(Triangle triangle, glm::vec3 planeNormal, glm::vec3 pointOnPlane)
{
	// If any of the 3 line segments are colliding, then there is a collision
	if (IsLineCollidingWithPlane(triangle.pointA, triangle.pointB, planeNormal, pointOnPlane) ||
		IsLineCollidingWithPlane(triangle.pointA, triangle.pointC, planeNormal, pointOnPlane) ||
		IsLineCollidingWithPlane(triangle.pointB, triangle.pointC, planeNormal, pointOnPlane))
	{
		std::cout << "Triangle is Colliding." << std::endl;
		return true;
	}

	// Otherwise no collision
	std::cout << "Triangle is NOT Colliding." << std::endl;
	return false;
}
