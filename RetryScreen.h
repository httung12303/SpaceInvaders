#pragma once
#include "BaseObject.h"
#include "Player.h"
#include "BasicFunction.h"

const int RETRY_NONE = -1;
const int RETRY_BUTTON = 0;
const int RETURN_TO_MAIN_MENU_BUTTON = 1;
const int RETRY_EXIT_BUTTON = 2;

class RetryScreen {
public:
	RetryScreen() {}
	RetryScreen(SDL_Renderer* screen);
	~RetryScreen();
	void handleInput(bool& inStartScreen, bool& exitGame);
	void show(SDL_Renderer* screen);
	bool TryAgain() { return tryAgain; }
	void resetTryAgainOption() { tryAgain = false; }
protected:
	int currentButton;
	bool tryAgain;
	BaseObject backGround;
	BaseObject title;
	BaseObject buttons[5];
	BaseObject highlightedButtons[5];
};