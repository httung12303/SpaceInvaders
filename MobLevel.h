#pragma once
#include "Player.h"
#include "Enemy.h"
#include "EnemyFormation.h"
#include "BaseObject.h"

class MobLevel {
public:
	MobLevel(SDL_Renderer* screen, const std::string& formationPath);
	~MobLevel();
	void process(Player& player, SDL_Renderer* screen);
	void handleInput(SDL_Event& event, Player& player, SDL_Window* window, SDL_Renderer* screen, bool& exitGame);
private:
	EnemyFormation* enemyFormation = NULL;
	BaseObject backGround;
};