#include "Input.h"
#include <iostream>
#include "Camera.h"

#include "Utility.h"



Input * Input::instance = NULL;


Input * Input::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Input();
	}
	return instance;
}


void Input::KeyboardDown(unsigned char key, int x, int y)
{
	if (GetInstance()->keyState[key] == UP)
	{
		GetInstance()->keyState[key] = DOWN_FIRST;
	}
	else
	{
		GetInstance()->keyState[key] = DOWN;
	}
}

void Input::KeyboardUp(unsigned char key, int x, int y)
{
	if (GetInstance()->keyState[key] == DOWN)
	{
		GetInstance()->keyState[key] = UP_FIRST;
	}
	else
	{
		GetInstance()->keyState[key] = UP;
	}
}

void Input::SpecialKeyboardDown(int key, int x, int y)
{
	if (GetInstance()->specialKeys[key] == UP)
	{
		GetInstance()->specialKeys[key] = DOWN_FIRST;
	}
	else
	{
		GetInstance()->specialKeys[key] = DOWN;
	}
}

void Input::SpecialKeyboardUp(int key, int x, int y)
{
	if (GetInstance()->specialKeys[key] == DOWN)
	{
		GetInstance()->specialKeys[key] = UP_FIRST;
	}
	else
	{
		GetInstance()->specialKeys[key] = UP;
	}
}

void Input::MouseClick(int button, int state, int x, int y)
{
	// Don't allow array overflow
	if (button >= 3)
		return;

	GetInstance()->mouseState[button] = (state == GLUT_DOWN) ? DOWN : UP;
}

void Input::MouseActiveMove(int x, int y)
{
	GetInstance()->ScreenSpaceToWorldSpace(x, y);
}

void Input::MousePassiveMove(int x, int y)
{

	GetInstance()->ScreenSpaceToWorldSpace(x, y);
}

int Input::GetMouseState(int button)
{
	return GetInstance()->mouseState[button];
}

char Input::GetKeyDown(char key)
{
	return GetInstance()->keyState[key];
}

int Input::GetSpecialKeyDown(int key)
{
	return GetInstance()->specialKeys[key];
}

glm::vec2 Input::GetMousePosition()
{
	return GetInstance()->mousePosition;
}

char Input::GetLastKeyDown()
{
	// Iterate through the keys
	for (int i = 0; i < 255; ++i)
	{
		// Return the key that is pressed
		if (GetInstance()->keyState[i] == DOWN)
		{
			return i;
		}
	}

	return ' ';
}

void Input::ScreenSpaceToWorldSpace(int x, int y)
{
	float halfScreenWidth = (float)Utility::GetScreenWidth() / 2; // TODO move to Utility
	float halfScreenHeight = (float)Utility::GetScreenHeight() / 2;

	GetInstance()->mousePosition.x = x - halfScreenWidth;
	GetInstance()->mousePosition.y = -y + halfScreenHeight;
	
}

void Input::ShutDownInput()
{
	delete instance;
	instance = NULL;
}



