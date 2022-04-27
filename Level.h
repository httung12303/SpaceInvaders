#pragma once
#include "BasicFunction.h"
#include "Player.h"
#include "PowerUp.h"

class PowerUpInfo {
public:
	PowerUpInfo(const SDL_Rect& rect, const int& effect) { this->rect = rect;  this->effect = effect; }
	SDL_Rect rect;
	int effect;
};

class Level {
public:
	Level(SDL_Renderer* screen);
	virtual void reset() { }
	virtual void process(Player& player, SDL_Renderer* screen) {}
	virtual void handleInput(SDL_Event& event, Player& player, SDL_Window* window, SDL_Renderer* screen, bool& inSettingsScreen, bool& exitGame) {  }
	void insertRandomPowerUp();
	void movePowerUps();
	void renderPowerUps(SDL_Renderer* screen);
	void playerPowerUp(Player& player);
protected:
	PowerUp* extraHitPointPowerUp = NULL;
	PowerUp* extraShotPowerUp = NULL;
	PowerUp* increaseAttackSpeedPowerUp = NULL;
	std::vector<PowerUpInfo> powerUps;
	unsigned int lastPowerUp;
};