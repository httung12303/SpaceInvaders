#pragma once
#include "RetryScreen.h"

const int VICTORY_NONE = -1;
const int NEXT_LEVEL_BUTTON = 0;
const int VICTORY_RETURN = 1;
const int VICTORY_EXIT = 2;

class VictoryScreen : public RetryScreen {
public:
	VictoryScreen(SDL_Renderer* screen);
	~VictoryScreen() { RetryScreen::~RetryScreen(); }
	void show(SDL_Renderer* screen, bool bossLevel);
	void handleInput(bool& inStartScreen, bool& exitGame);
	bool playNextLevel() { return nextLevel; }
	void resetNextLevelOption() { nextLevel = false; }
private:
	bool nextLevel;
};