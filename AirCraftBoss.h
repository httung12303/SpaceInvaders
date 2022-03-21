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
	void showProjectiles(SDL_Renderer* des, const SDL_Rect& playerHitbox);
	void showOrbCircle(SDL_Renderer* screen);
	SDL_Rect getHitBox() { return objRect; }
	std::vector<SDL_Rect> getOrbCircle() { return orbCircle; }
	std::vector<bool> getOrbState() { return orbDeleted; }
	std::vector<SDL_Rect> getHomingMissilesRect() { return homingMissilesRect; }
	std::vector<bool> getHomingMissilesState() { return homingMissilesDeleted; }
	void deleteOrb(int i) { orbDeleted[i] = true; }
	std::vector<SDL_Rect> getHitBoxes();
	void moveHomingMissiles(const SDL_Rect& playerHitbox);
	void showHomingMissiles(SDL_Renderer* screen);
	void deleteHomingMissile(int i) { homingMissilesDeleted[i] = true; }
private:
	unsigned int lastMove;
	unsigned int lastOrbCircle;
	unsigned int lastHomingMissiles;
	int targetCenter;
	BaseObject orb;
	BaseObject homingMissile;
	std::vector<SDL_Rect> orbCircle;
	std::vector<bool> orbDeleted;
	std::vector<SDL_Rect> homingMissilesRect;
	std::vector<double> homingMissilesAngle;
	std::vector<bool> homingMissilesDeleted;
};