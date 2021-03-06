#include "Mesh2D_Quad.h"
#include "Texture.h"
#include "ShaderLoader.h"


Mesh2D_Quad::Mesh2D_Quad(GameObject * owner)
{
	this->owner = owner;
}


Mesh2D_Quad::~Mesh2D_Quad()
{
}

void Mesh2D_Quad::Initialise()
{


	GLfloat quad[] = 
	{
		// position				// color			// Tex Coords
		-0.5f,  0.0f,  0.5f,	0.0f, 1.0f, 1.0f,	0.0f, 0.0f,		// Top Left
		+0.5f,  0.0f,  0.5f,	0.0f, 1.0f, 1.0f,	1.0f, 0.0f,		// Top Right
		-0.5f,  0.0f, -0.5f,	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,		// Bottom Left
		+0.5f,  0.0f, -0.5f,	0.0f, 1.0f, 1.0f,	1.0f, 1.0f		// Bottom Right
	};

	GLuint indicies[] =
	{
		0, 2, 1,	// Top Left
		2, 3, 1		// Bottom Right
	};

	indexCount = 6;

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(quad),
		quad,
		GL_STATIC_DRAW
	);

	// Binding Vertext attributes
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(0)
	);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat))
	);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indicies),
		indicies,
		GL_STATIC_DRAW
	);
}




