#pragma once
#include "BasicFunction.h"
#include "Player.h"
class Level {
public:
	virtual void reset() { }
	virtual void process(Player& player, SDL_Renderer* screen) {  }
	virtual void handleInput(SDL_Event& event, Player& player, SDL_Window* window, SDL_Renderer* screen, bool& inSettingsScreen, bool& exitGame) {  }
};