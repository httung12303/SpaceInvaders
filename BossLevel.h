#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"
#include "AirCraftBoss.h"
#include "Player.h"
#include "Level.h"

class BossLevel : public Level {
public:
	BossLevel(SDL_Renderer* screen);
	~BossLevel();
	void process(Player& player, SDL_Renderer* screen);
	void handleInput(SDL_Event& event, Player& player, SDL_Window* window, SDL_Renderer* screen, bool& inSettingsScreen, bool& exitGame);
	void reset() { boss->reset(); }
	bool bossDefeated() { return !boss->isAlive(); }
private:
	AirCraftBoss* boss = NULL;
	BaseObject backGround;
};