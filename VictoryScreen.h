#pragma once
#include "RetryScreen.h"

//const int NONE = -1;
//const int NEXT_LEVEL_BUTTON = 0;
//const int RETURN_TO_MAIN_MENU_BUTTON = 1;
//const int EXIT_BUTTON = 2;
//const int RESTART_BUTTON = 3;
//const int RESTART_BOSS_LEVEL_BUTTON = 4;

class VictoryScreen : public RetryScreen {
public:
	VictoryScreen(SDL_Renderer* screen);
	~VictoryScreen() { RetryScreen::~RetryScreen(); }
	void show(SDL_Renderer* screen, bool bossLevel);
	void handleInput(bool& inStartScreen, bool& exitGame, bool bossLevel);
	bool playNextLevel() { return nextLevel; }
	bool restartGame() { return restart; }
	bool replayBossLevel() { return replayBoss; }
	void resetNextLevelOption() { nextLevel = false; }
	void resetRestartOption() { restart = false; }
	void resetReplayBossOption() { replayBoss = false; }
	
private:
	bool nextLevel;
	bool restart;
	bool replayBoss;
};