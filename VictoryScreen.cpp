#include "VictoryScreen.h"

VictoryScreen::VictoryScreen(SDL_Renderer* screen) {
	title.loadImage("images/VictoryScreen/Title.png", screen);
	buttons[0].loadImage("images/VictoryScreen/NextLevel.png", screen);
	buttons[1].loadImage("images/VictoryScreen/Return.png", screen);
	buttons[2].loadImage("images/VictoryScreen/Exit.png", screen);
	highlightedButtons[0].loadImage("images/VictoryScreen/highlightedNextLevel.png", screen);
	highlightedButtons[1].loadImage("images/VictoryScreen/highlightedReturn.png", screen);
	highlightedButtons[2].loadImage("images/VictoryScreen/highlightedExit.png", screen);
	backGround.loadImage("images/Background/sky.png", screen);
	backGround.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Rect renderQuad = { WINDOW_WIDTH / 2 - title.getRect().w / 2, 150, title.getRect().w, title.getRect().h };
	title.setRect(renderQuad);
	for (int i = 0; i < 3; i++) {
		renderQuad = { WINDOW_WIDTH / 2 - buttons[i].getRect().w / 2, 350 + 70 * i, buttons[i].getRect().w, buttons[i].getRect().h };
		buttons[i].setRect(renderQuad);
		highlightedButtons[i].setRect(renderQuad);
	}
	currentButton = VICTORY_NONE;
}

void VictoryScreen::show(SDL_Renderer* screen, bool bossLevel) {
	SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
	SDL_RenderClear(screen);
	backGround.render(screen, NULL);
	title.render(screen, NULL);
	if (!bossLevel) {
		if (currentButton == NEXT_LEVEL_BUTTON) {
			highlightedButtons[0].render(screen, NULL);
		}
		else {
			buttons[0].render(screen, NULL);
		}
	}
	if (currentButton == VICTORY_RETURN) {
		highlightedButtons[1].render(screen, NULL);
	}
	else {
		buttons[1].render(screen, NULL);
	}
	if (currentButton == VICTORY_EXIT) {
		highlightedButtons[2].render(screen, NULL);
	}
	else {
		buttons[2].render(screen, NULL);
	}
	SDL_RenderPresent(screen);
}

void VictoryScreen::handleInput(bool& inStartScreen, bool& exitGame) {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			exitGame = true;
			inStartScreen = false;
		}
		else if (event.type == SDL_MOUSEMOTION) {
			int x = event.motion.x;
			int y = event.motion.y;
			if (pointInsideRect(x, y, buttons[0].getRect())) {
				currentButton = NEXT_LEVEL_BUTTON;
			}
			else if (pointInsideRect(x, y, buttons[1].getRect())) {
				currentButton = VICTORY_RETURN;
			}
			else if (pointInsideRect(x, y, buttons[2].getRect())) {
				currentButton = VICTORY_EXIT;
			}
			else {
				currentButton = VICTORY_NONE;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (currentButton == NEXT_LEVEL_BUTTON) {
				inStartScreen = false;
				exitGame = false;
				nextLevel = true;
			}
			else if (currentButton == VICTORY_RETURN) {
				inStartScreen = true;
				exitGame = false;
				nextLevel = false;
			}
			else if (currentButton == VICTORY_EXIT) {
				exitGame = true;
				inStartScreen = false;
				nextLevel = false;
			}
		}
	}
}