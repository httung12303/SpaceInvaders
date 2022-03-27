#pragma once
#include "BasicFunction.h"
#include "BaseObject.h"

const int SETTINGS_MUSIC_ON_BUTTON = 1;
const int SETTINGS_EXIT_BUTTON = 3;
const int SETTINGS_RETURN_BUTTON = 4;
const int SETTINGS_NONE = -1;

class SettingsScreen {
public:
	SettingsScreen(SDL_Renderer* screen);
	~SettingsScreen();
	void handleInput(bool& inSettingsScreen, bool& musicPlaying, bool& exitGame);
	void show(SDL_Renderer* screen, const bool& musicPlaying);
private:
	int currentButton;
	BaseObject backGround;
	BaseObject title;
	BaseObject musicOn;
	BaseObject musicOff;
	BaseObject exitButton;
	BaseObject returnButton;
	BaseObject highlightedMusicOn;
	BaseObject highlightedMusicOff;
	BaseObject highlightedExitButton;
	BaseObject highlightedReturnButton;
};