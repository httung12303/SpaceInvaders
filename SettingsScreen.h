#pragma once
#include "BasicFunction.h"
#include "BaseObject.h"
#include "Level.h"
#include "Player.h"

const int SETTINGS_MUSIC_ON_BUTTON = 1;
const int SETTINGS_RETRY = 2;
const int SETTINGS_EXIT_BUTTON = 3;
const int SETTINGS_RETURN_BUTTON = 4;
const int SETTINGS_RETURN_TO_MENU_BUTTON = 5;
const int SETTINGS_NONE = -1;

class SettingsScreen {
public:
	SettingsScreen(SDL_Renderer* screen);
	~SettingsScreen();
	void handleInput(bool& inStartScreen, bool& inSettingsScreen, bool& musicPlaying, bool& exitGame, Player*& player, Level*& level, const bool& playing);
	void show(SDL_Renderer* screen, const bool& musicPlaying, const bool& playing);
private:
	int currentButton;
	BaseObject backGround;
	BaseObject title;
	BaseObject buttons[6];
	BaseObject highlightedButtons[6];
};