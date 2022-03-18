#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"
#include "Enemy.h"

const int MAX_BOSS_HP = 300;
const int BOSS_SPEED = 4;

class AirCraftBoss : public Enemy {
public:
	AirCraftBoss(SDL_Renderer* screen);
	~AirCraftBoss();
	void moveTowardsPlayer(const SDL_Rect& playerHitbox);
	void shoot();
	//void interactWithPlayer(Player& player);
	void moveOrbCircle();
	void showProjectiles(SDL_Renderer* des);
	void showOrbCircle(SDL_Renderer* screen);
	SDL_Rect getHitBox() { return objRect; }
	std::vector<SDL_Rect> getOrbCircle() { return orbCircle; }
	std::vector<bool> getOrbState() { return orbDeleted; }
	void deleteOrb(int i) { orbDeleted[i] = true; }
	std::vector<SDL_Rect> getHitBoxes();
private:
	unsigned int lastMove;
	unsigned int lastOrbCircle;
	int targetCenter;
	int tripleStandardHit = 0;
	BaseObject orb;
	std::vector<SDL_Rect> orbCircle;
	std::vector<bool> orbDeleted;
};