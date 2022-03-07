#pragma once
#include "BaseObject.h";
#include "Enemy.h"
#include "Player.h"

const std::string STACKED_FORMATION_PATH = "formations/StackedFormation.txt";
class EnemyFormation {
public:
	EnemyFormation(const std::string path);
	~EnemyFormation();
	void loadEnemies(const std::string imagePath, SDL_Renderer* screen);
	void show(SDL_Renderer* screen);
	void interactWithPlayer(Player& player);
private:
	std::vector<Enemy> enemies;
	int formationVerticalDirection = 0;
	int formationHorizontalDirection = 0;
	std::string formationType = "";
};