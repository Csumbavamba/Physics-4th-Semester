#include "GameObject.h"
#include "Camera.h"


GameObject::GameObject()
{
	objectDiameter = 1.0f;
}
GameObject::~GameObject()
{
}

float GameObject::GetObjectDiamater() const
{
	return objectDiameter;
}

void GameObject::SetCamera(Camera * camera)
{
	this->camera = camera;
}
