#pragma once
#include "GameObject.h"

class Mesh2D_Quad;

class UI_Image : public GameObject
{
public:
	UI_Image(Camera * camera, std::string imagePath);
	virtual ~UI_Image();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	void Update(float deltaTime);

private:
	GLuint imageProgram;
	Mesh2D_Quad * backgroundImage = NULL;
};

