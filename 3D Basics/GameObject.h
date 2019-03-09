#pragma once

#include <string>

#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "Transform.h"

class Camera;
class Collider_Sphere;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialise() = 0;
	virtual void Render(GLuint program) = 0;

	float GetObjectDiamater() const;
	void SetCamera(Camera * camera);

	Transform transform;

protected:
	float objectDiameter;
	Camera * camera = NULL;
	
};

