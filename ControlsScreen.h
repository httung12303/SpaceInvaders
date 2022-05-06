#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"

class ControlsScreen {
public:
	ControlsScreen(SDL_Renderer* screen);
	~ControlsScreen();
	void handleInput(bool& inControlsScreen, bool& inSettingsScreen, bool& exitGame);
	void show(SDL_Renderer* screen);
private:
	BaseObject screenTemplate;
	BaseObject buttons[2];
	int currentButton;
};