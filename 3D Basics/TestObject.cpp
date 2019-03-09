#include "TestObject.h"
#include "Mesh_Cube.h"
#include "Mesh_Pyramid.h"
#include "Mesh2D_Quad.h"
#include "Mesh_Sphere.h"
#include "Model.h"
#include "Texture.h"
#include "Camera.h"



TestObject::TestObject(Camera * camera)
{
	this->camera = camera;
	objectDiameter = 3.0f;

	mesh = new Mesh2D_Quad(this);
}


TestObject::~TestObject()
{
	delete mesh;
	mesh = NULL;

	// Delete gameObject
	GameObject::~GameObject();
}

void TestObject::Initialise()
{
	// mesh->Initialise();
	transform.scale *= objectDiameter;

	// Last call
	mesh->Initialise();
}


void TestObject::Render(GLuint program)
{
	mesh->Render(camera, program);

}

void TestObject::Update(float deltaTime)
{
	mesh->Update();
}

void TestObject::AddTexturePath(std::string path)
{
	// mesh->GetTexture()->SetTexturePath(path);
}
