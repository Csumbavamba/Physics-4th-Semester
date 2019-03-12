#pragma once
#include "GameObject.h"
#include "CapsuleSettings.h"

class Mesh2D_Quad;

class Capsule :
	public GameObject
{
public:
	Capsule(Camera * mainCamera);
	virtual ~Capsule();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime);

	void SetupSettings(CapsuleSettings settings);

private:
	CapsuleSettings capsuleSettings;
	Mesh2D_Quad * mesh = NULL;
};

