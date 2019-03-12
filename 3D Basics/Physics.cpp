#include "Physics.h"
#include <iostream>
#include "Transform.h"

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
		<< ", " << planeNormalVector.z << std::endl;

	// Find the value of the reference distance and the distance between the  points
	float fromPlanePosition = glm::dot((pointToCheck - pointOnPlane), planeNormalVector);


	// See if it's on the plane
	if (fromPlanePosition == 0)
	{
		std::cout << "it is on the plane" << std::endl;
		return PlaneState::ONPLANE;
	}
	// In Front of the plane
	else if (fromPlanePosition > 0)
	{
		std::cout << "It is Infront of the plane" << std::endl;
		return PlaneState::INFRONT;
	}
	// Behind the plane
	else
	{
		std::cout << "It is Behind the plane" << std::endl;
		return PlaneState::BEHIND;
	}
}

void Physics::ProveLagrangeValid(glm::vec3 vector1, glm::vec3 vector2, glm::vec3 vector3)
{
	// If the result is the same it's valid, otherwise it is not
	if (glm::dot(vector1, glm::cross(vector2, vector3)) == glm::dot(vector2, glm::cross(vector1, vector3)))
	{
		std::cout << "Lagrange formula is valid." << std::endl;
	}
	else
	{
		std::cout << "Lagrange formula is not valid." << std::endl;
	}
}

bool Physics::IsLineCollidingWithPlane(glm::vec3 linePoint1, glm::vec3 linePoint2, glm::vec3 planeNormal, glm::vec3 pointOnPlane)
{
	// Print given details
	std::cout << "Checking whether Line Segment with Points of: "
		<< linePoint1.x
		<< ", " << linePoint1.y
		<< ", " << linePoint1.z
		<< " and : "
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
		<< std::endl;

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

float Physics::GetShortestDistanceBetweenLineSegments(LineSegment segment1, LineSegment segment2)
{
	// Get the distance between point and line segment (4 times)
	
	float potentialShortestDistances [3];

	// By default start with p1
	float shortestDistance = GetDistanceToSegment2D(segment1.pointA, segment2);
	
	// Calculate P2 distance
	potentialShortestDistances[0] = GetDistanceToSegment2D(segment1.pointB, segment2);
	// Calculate P3 distance
	potentialShortestDistances[1] = GetDistanceToSegment2D(segment2.pointA, segment1);
	// Calculate P4 distance
	potentialShortestDistances[2] = GetDistanceToSegment2D(segment2.pointB, segment1);

	// Choose the shortest distance
	for (int i = 0; i < 3; i++)
	{
		if (potentialShortestDistances[i] < shortestDistance)
		{
			shortestDistance = potentialShortestDistances[i];
		}
	}

	return shortestDistance;
}

float Physics::GetDistanceToSegment2D(glm::vec3 point, LineSegment segment)
{
	glm::vec2 lineDistanceVector;

	lineDistanceVector.x = segment.pointA.x - segment.pointB.x;
	lineDistanceVector.y = segment.pointA.y - segment.pointB.y;

	// In this case it's not a segment but a point
	if (lineDistanceVector.x == 0 && lineDistanceVector.y == 0)
	{	
		// This is 2D
		lineDistanceVector.x = point.x - segment.pointA.x;
		lineDistanceVector.y = point.y - segment.pointB.z;


		// Distance between 2 points
		return std::sqrt(std::pow(lineDistanceVector.x, 2.0f) + std::pow(lineDistanceVector.y, 2.0f));
	}

	// Calculate t to minimize the distance
	float t = ((point.x - segment.pointA.x) * lineDistanceVector.x + (point.y - segment.pointA.y) * lineDistanceVector.y) /
		(std::pow(lineDistanceVector.x, 2.0f) + std::pow(lineDistanceVector.y, 2.0f));

	// Closest point is point1
	if (t < 0)
	{
		return Transform::GetDistance2D(point, segment.pointA);
	}
	// Closest point is point2
	else if (t > 0)
	{
		return Transform::GetDistance2D(point, segment.pointB);
	}
	// On the segment
	else
	{
		// The Y is fixed
		glm::vec3 closestPointOnSegment = glm::vec3(
			segment.pointA.x + t * lineDistanceVector.x,
			0.0f,
			segment.pointA.z + t * lineDistanceVector.y);

		return Transform::GetDistance2D(closestPointOnSegment, point);
	}
}

bool Physics::IsCapsuleColliding(CapsuleSettings capsule1, CapsuleSettings capsule2)
{
	// If the radius between the 2 capsules is smaller than the shortest distance
	if (capsule1.radius + capsule2.radius > GetInstance()->GetShortestDistanceBetweenLineSegments(capsule1.lineSegment, capsule2.lineSegment))
	{
		return true;
	}

	return false;
}

void Physics::ShutDown()
{
	delete instance;
	instance = NULL;
}