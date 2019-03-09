#include "GameManager_3D.h"

#include "Camera.h"
#include "ShaderLoader.h"
#include "FileWriting.h"
#include "Utility.h"
#include "Input.h" // not used


#pragma comment(lib, "Ws2_32.lib")

GameManager_3D * GameManager_3D::instance = NULL;

GameManager_3D::GameManager_3D()
{
	deltaTime = 0.0f;
	mainCamera = new Camera(PERSPECTIVE);


	// PHYSICS Elements
	pointOnPlane = glm::vec3(1.0f, 1.0f, 1.0f);
	planeNormalVector = glm::vec3(1.0f, 0.0f, 0.0f);
	pointInAir = glm::vec3(1.0f, 5.0f, 5.0f);
	triangle = Triangle(glm::vec3(1.0f, 5.0f, 5.0f), glm::vec3(3.0f, 5.0f, 5.0f), glm::vec3(4.0f, 4.0f, 1.0f)); // First point should be on the plane

}


GameManager_3D::~GameManager_3D()
{
	// GameObjects
	delete mainCamera;
	mainCamera = NULL;

	// Static Deletes
	ShaderLoader::ShutDownShaderLoader();
	Input::ShutDownInput();
	Utility::ShutDown();
}

GameManager_3D * GameManager_3D::GetInstance()
{
	if (instance == NULL)
	{
		instance = new GameManager_3D();
	}
	return instance;;
}

void GameManager_3D::PlayGame(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Norton Defender");

	glClearColor(0.0, 0.0, 0.0, 1.0); // Clear Window


	glewInit(); // ADD FUNCTIONS AFTER THIS

	// Enable Culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Enable Depth for Rendering
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Blend between textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GetInstance()->Initialise();

	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	// Input stuff
	glutKeyboardFunc(Input::KeyboardDown);
	glutKeyboardUpFunc(Input::KeyboardUp);
	glutSpecialFunc(Input::SpecialKeyboardDown);
	glutSpecialUpFunc(Input::SpecialKeyboardUp);
	glutMouseFunc(Input::MouseClick);
	glutMotionFunc(Input::MouseActiveMove);
	glutPassiveMotionFunc(Input::MousePassiveMove);

	glutCloseFunc(GameManager_3D::ShutDownGame);
	glutMainLoop();

	return;
}

void GameManager_3D::Initialise()
{
	// Create Programs
	lightingProgram = ShaderLoader::GetInstance()->CreateProgram("Phong-VertexShader.vs", "Phong-FragmentShader.fs");


	// Do calculations here

	// Proving Lagrange
	Physics::ProveLagrangeValid(
		GetInstance()->pointOnPlane,
		GetInstance()->pointInAir,
		glm::vec3(2.0f, 2.0f, 2.0f)
	);
	
	// Check if the point is on Plane
	Physics::GetInstance()->IsPointOnPlane(
		GetInstance()->pointInAir, 
		GetInstance()->planeNormalVector, 
		GetInstance()->pointOnPlane);

	// Line Segment Collision
	Physics::IsLineCollidingWithPlane(
		glm::vec3(5.0f, 10.0f, 5.0f),
		glm::vec3(1.0f, 5.0f, 5.0f),
		GetInstance()->planeNormalVector,
		GetInstance()->pointOnPlane
	);

	// Check for Triangle collision
	Physics::IsTriangleCollidingWithPlane(
		GetInstance()->triangle,
		GetInstance()->planeNormalVector,
		GetInstance()->pointOnPlane);



	// Deltatime calculation
	previousTimeStamp = (float)glutGet(GLUT_ELAPSED_TIME);

	mainCamera->Initialise();

}

void GameManager_3D::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0); // clear red

	// Do rendering here


	glBindVertexArray(0); // Unbind VAO
	glUseProgram(0);

	glutSwapBuffers();
}

void GameManager_3D::Update()
{
	// Time Calculation
	float currentTime = (float)glutGet(GLUT_ELAPSED_TIME);
	GetInstance()->deltaTime = (currentTime - GetInstance()->previousTimeStamp) * 0.001f;
	GetInstance()->previousTimeStamp = currentTime;

	// Update Screen size
	Utility::Update();

	// Camera Update
	GetInstance()->mainCamera->Update(GetInstance()->deltaTime);


	


	// Last function call
	glutPostRedisplay();
}


void GameManager_3D::ShutDownGame()
{
	GetInstance()->fileWritingObject->WriteToFile(GetInstance()->outputString);
	delete instance;
	instance = NULL;
}
