#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"

const int TITLE_FALL_SPEED = 2;

class StartScreen {
public:
	StartScreen(SDL_Renderer* screen);
	~StartScreen();
	void resetTitlePos();
	void show(SDL_Renderer* screen);
	void handleInput(SDL_Event& event, SDL_Window*& window, bool& inStartScreen, bool& inSettingsScreen, bool& gameOver);
	void playMusic(const bool& musicPlaying);
private:
	BaseObject title;
	BaseObject background;
	BaseObject buttons[3];
	BaseObject highlightedButtons[3];
	Mix_Music* startScreenMusic = NULL;
	int currentButton;
};