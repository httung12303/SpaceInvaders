#pragma once
#include "BaseObject.h";
#include "Enemy.h"
#include "Player.h"

class EnemyFormation {
public:
	EnemyFormation(const std::string path);
	~EnemyFormation();
	void loadEnemies(const std::string imagePath, SDL_Renderer* screen);
	void loadProjectiles(const std::string path, SDL_Renderer* screen);
	void show(SDL_Renderer* screen);
	void interactWithPlayer(Player& player);
	void moveFormation();
private:
	std::vector<Enemy> enemies;
	int formationVerticalDirection = 0;
	int formationHorizontalDirection = 0;
	std::string formationType = "";
	int moveState = 0;
	int lastMove = 0;
};