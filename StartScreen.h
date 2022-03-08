#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"

const int TITLE_FALL_SPEED = 2;

const int NONE = 0;
const int START_BUTTON = 1;
const int EXIT_BUTTON = 2;

class StartScreen {
public:
	StartScreen(SDL_Renderer* screen);
	~StartScreen();
	void resetTitlePos();
	void show(SDL_Renderer* screen);
	void handleInput(SDL_Event& event, SDL_Window*& window, bool& inStartScreen, bool& gameOver);
private:
	BaseObject title;
	BaseObject background;
	BaseObject startButton;
	BaseObject exitButton;
	BaseObject highlightedStartButton;
	BaseObject highlightedExitButton;
	int currentButton;
};