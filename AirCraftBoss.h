#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"
#include "Player.h"

const int MAX_BOSS_HP = 300;
const int BOSS_SPEED = 4;

class AirCraftBoss : public BaseObject {
public:
	AirCraftBoss(SDL_Renderer* screen);
	~AirCraftBoss();
	void show(SDL_Renderer* screen);
	bool isAlive() { return alive; }
	void moveTowardsPlayer(const SDL_Rect& playerHitbox);
private:
	int hp;
	bool alive;
	unsigned int lastMove;
	int targetCenter;
};