#pragma once
#include "Player.h"
#include "Enemy.h"
#include "EnemyFormation.h"
#include "BaseObject.h"
#include "Level.h"

class MobLevel : public Level {
public:
	MobLevel(SDL_Renderer* screen, const std::string& formationPath);
	~MobLevel();
	void process(Player& player, SDL_Renderer* screen);
	void handleInput(SDL_Event& event, Player& player, SDL_Window* window, SDL_Renderer* screen, bool& inSettingsScreen, bool& exitGame);
	void reset() { enemyFormation->reset();  }
	bool mobLevelDefeated() { return enemyFormation->getNumberOfEnemies() == 0; }
private:
	EnemyFormation* enemyFormation = NULL;
	BaseObject backGround;
};