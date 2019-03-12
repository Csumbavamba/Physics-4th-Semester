#include "Capsule.h"
#include "Mesh2D_Quad.h"
#include "Texture.h"



Capsule::Capsule(Camera * mainCamera)
{
	this->camera = mainCamera;
	mesh = new Mesh2D_Quad(this);
}


Capsule::~Capsule()
{
	delete mesh;
	mesh = NULL;
}

void Capsule::Initialise()
{
	mesh->Initialise();
	// mesh->GetTexture()->SetTexturePath("SETITHERE"); -> TODO add good path
}

void Capsule::Render(GLuint program)
{
	mesh->Render(camera, program);
}

void Capsule::Update(float deltaTime)
{
	mesh->Update();
}

void Capsule::SetupSettings(CapsuleSettings settings)
{
	this->capsuleSettings = settings;
}
