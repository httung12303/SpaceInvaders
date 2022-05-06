#pragma once
#include "BasicFunction.h"
#include "BaseObject.h"
#include "Level.h"
#include "Player.h"

class SettingsScreen {
public:
	SettingsScreen(SDL_Renderer* screen);
	~SettingsScreen();
	void handleInput(bool& inStartScreen, bool& inSettingsScreen, bool& musicPlaying, bool& exitGame, Player*& player, Level*& level, const bool& playing, bool& inControlsScreen);
	void show(SDL_Renderer* screen, const bool& musicPlaying, const bool& playing);
private:
	int currentButton;
	BaseObject backGround;
	BaseObject title;
	BaseObject buttons[7];
	BaseObject highlightedButtons[7];
};