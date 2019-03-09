#pragma once
#include "GameObject.h"

class TextLabel;
class AudioSound;
class AudioSystem;

class UI_Button : public GameObject
{
public:
	UI_Button(std::string menuTitle, glm::vec2 position, AudioSystem * system);
	virtual ~UI_Button();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	void Update(float deltaTime);

	void SetScale(float scale);
	void SetFont(std::string font);
	void SetText(std::string text);
	bool IsClicked() const;
	void Reset();

	

private:
	void SetupAudio(AudioSystem * system);
	bool isClicked;
	TextLabel * button = NULL;
	AudioSound * clickSound = NULL;

};

