#pragma once

// Vertices and Textures
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

// FOR PHYSICS
#include "Physics.h"

#include <vector>
#include <thread>

class ShaderLoader;
class Camera;
class FileWriting;

class GameManager_3D
{
public:
	static GameManager_3D * GetInstance();

	static void PlayGame(int argc, char **argv);
	void Initialise();
	
	static void Render();
	static void Update();
	static void ShutDownGame();

	float deltaTime;


private:

	// Singleton
	GameManager_3D();
	~GameManager_3D();
	GameManager_3D(const GameManager_3D& copy) {};
	GameManager_3D& operator= (const GameManager_3D& move) {};

	static GameManager_3D * instance;

	GLuint lightingProgram;
	
	// For deltatime
	float previousTimeStamp;

	// Logging
	std::string outputString;
	FileWriting * fileWritingObject = NULL;

	// Gameobjects
	Camera * mainCamera = NULL;


	// Physics test
	glm::vec3 pointOnPlane;
	glm::vec3 planeNormalVector;
	glm::vec3 pointInAir;

	Triangle triangle;

};

