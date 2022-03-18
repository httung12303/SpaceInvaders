#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"

const int MAX_BOSS_HP = 300;

class AirCraftBoss : public BaseObject {
public:
	AirCraftBoss();
	~AirCraftBoss();
private:
	int hp;
};