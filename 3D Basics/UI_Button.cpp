#include "UI_Button.h"
#include "TextLabel.h"
#include "Input.h"

#include "AudioSound.h"
#include "AudioSystem.h"



UI_Button::UI_Button(std::string menuTitle, glm::vec2 position, AudioSystem * system)
{
	std::string font = "Dependencies/Fonts/introrustg-base2line.otf";
	isClicked = false;
	button = new TextLabel(menuTitle, font, position);
	clickSound = new AudioSound("Audio/Click.wav", FMOD_DEFAULT);

	SetupAudio(system);
}


UI_Button::~UI_Button()
{
	delete button;
	button = NULL;

	delete clickSound;
	clickSound = NULL;
}

void UI_Button::Initialise()
{
	button->Initialise();
}

void UI_Button::Render(GLuint program)
{
	button->Render(NULL);
}

void UI_Button::Update(float deltaTime)
{
	button->Update();

	// Get the location of the mouse
	glm::vec2 mousePosition = Input::GetMousePosition();
	glm::vec3 mouseTransformedPosition = glm::vec3(mousePosition.x, 0.0f, mousePosition.y);

	if (button->GetCollider()->IsColliding(mouseTransformedPosition))
	{
		button->SetScale(1.2f);
		button->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

		// If Mouse clicked
		if (Input::GetMouseState(MOUSE_LEFT) == DOWN)
		{
			if (!isClicked)
			{
				// Play Click Sound
				clickSound->PlaySound();
			}

			// Change Menu state
			isClicked = true;
			
		}
	}
	else
	{
		button->SetScale(1.0f);
		button->SetColor(glm::vec3(0.8f, 0.8f, 0.8f));
	}
}

void UI_Button::SetupAudio(AudioSystem * system)
{
	clickSound->SetAudioSystem(system);
	clickSound->Initialise();
}

void UI_Button::SetScale(float scale)
{
	button->SetScale(scale);
}

void UI_Button::SetFont(std::string font)
{
	button->SetFont(font);
}

void UI_Button::SetText(std::string text)
{
	button->SetText(text);
}

bool UI_Button::IsClicked() const
{
	return isClicked;
}


void UI_Button::Reset()
{
	isClicked = false;
}
