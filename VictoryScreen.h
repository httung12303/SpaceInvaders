#pragma once
#include "RetryScreen.h"

const int VICTORY_NONE = -1;
const int NEXT_LEVEL_BUTTON = 0;
const int VICTORY_RETURN = 1;
const int VICTORY_EXIT = 2;
const int VICTORY_RESTART = 3;
const int VICTORY_REPLAY_BOSS_LEVEL = 4;

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