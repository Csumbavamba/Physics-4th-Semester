#include "UI_Image.h"
#include "Mesh2D_Quad.h"
#include "Texture.h"
#include "ShaderLoader.h"



UI_Image::UI_Image(Camera * camera, std::string imagePath)
{
	// Setup Background Image
	backgroundImage = new Mesh2D_Quad(this);
	backgroundImage->GetTexture()->SetTexturePath(imagePath);
	backgroundImage->GetTexture()->Initialise();
	this->camera = camera;

	transform.rotation.y = 180.0f;
	transform.scale.y *= 2.0f;

	// Create Background Program
	imageProgram = ShaderLoader::GetInstance()->CreateProgram("VertexShader.vs", "FragmentShader.fs");
}


UI_Image::~UI_Image()
{
	delete backgroundImage;
	backgroundImage = NULL;
}

void UI_Image::Initialise()
{
	backgroundImage->Initialise();

	transform.scale.x *= 100;
	transform.scale.z *= 100;
}

void UI_Image::Render(GLuint program)
{
	// Enable Culling
	glDisable(GL_CULL_FACE);
	backgroundImage->Render(camera, imageProgram);
	glEnable(GL_CULL_FACE);
}

void UI_Image::Update(float deltaTime)
{
	backgroundImage->Update();
}
