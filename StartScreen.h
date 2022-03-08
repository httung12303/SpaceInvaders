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
private:
	BaseObject title;
	BaseObject background;
};