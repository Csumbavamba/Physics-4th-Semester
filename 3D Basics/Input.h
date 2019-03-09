#pragma once
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#define Escape 27

enum MouseState
{
	MOUSE_LEFT, // 0
	MOUSE_MIDDLE, // 1
	MOUSE_RIGHT // 2
};

enum InputState
{
	UP,
	DOWN,
	UP_FIRST,
	DOWN_FIRST
};



class Input
{
public:
	static Input * GetInstance();

	static void KeyboardDown(unsigned char key, int x, int y);
	static void KeyboardUp(unsigned char key, int x, int y);
	static void SpecialKeyboardDown(int key, int x, int y);
	static void SpecialKeyboardUp(int key, int x, int y);

	static void MouseClick(int button, int state, int x, int y);
	static void MouseActiveMove(int x, int y);
	static void MousePassiveMove(int x, int y);

	static int GetMouseState(int button);
	static char GetKeyDown(char key);
	static int GetSpecialKeyDown(int key);
	static glm::vec2 GetMousePosition();

	static char GetLastKeyDown();

	void ScreenSpaceToWorldSpace(int x, int y);

	static void ShutDownInput();

private:
	Input() {};
	~Input() {};
	Input(const Input& copy) {};
	Input& operator= (const Input& move) {};

	static Input * instance;

	glm::vec2 mousePosition;

	InputState mouseState[3];
	InputState keyState[255];
	InputState specialKeys[255]; // TODO look up the actual number
};

