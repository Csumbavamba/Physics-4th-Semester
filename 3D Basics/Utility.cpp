#include "Utility.h"

Utility * Utility::instance = NULL;

int Utility::GetScreenWidth()
{
	return GetInstance()->screenWidth;
}

int Utility::GetScreenHeight()
{
	return GetInstance()->screenHeight;
}

void Utility::Update()
{
	GetInstance()->screenWidth = glutGet(GLUT_WINDOW_WIDTH);
	GetInstance()->screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
}

void Utility::ShutDown()
{
	delete instance;
	instance = NULL;
}
