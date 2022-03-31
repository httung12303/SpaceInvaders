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
	void reset();
	int getNumberOfEnemies() { return enemiesAlive; }
private:
	std::vector<Enemy> enemies;
	std::string formationType = "";
	int moveState = 0;
	int lastMove = 0;
	int xPosArr[100];
	int yPosArr[100];
	int startPosX[100];
	int startPosY[100];
	int posIndex[100];
	int enemiesAlive = 0;
};