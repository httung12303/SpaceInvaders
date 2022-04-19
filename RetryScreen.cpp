#include "RetryScreen.h"

RetryScreen::RetryScreen(SDL_Renderer* screen) {
	title.loadImage("images/RetryScreen/Title.png", screen);
	buttons[0].loadImage("images/RetryScreen/Retry.png", screen);
	buttons[1].loadImage("images/RetryScreen/Return.png", screen);
	buttons[2].loadImage("images/RetryScreen/Exit.png", screen);
	highlightedButtons[0].loadImage("images/RetryScreen/highlightedRetry.png", screen);
	highlightedButtons[1].loadImage("images/RetryScreen/highlightedReturn.png", screen);
	highlightedButtons[2].loadImage("images/RetryScreen/highlightedExit.png", screen);
	backGround.loadImage(GALAXY_BACKGROUND_PATH, screen);
	backGround.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);	
	SDL_Rect renderQuad = { WINDOW_WIDTH / 2 - title.getRect().w / 2, 150, title.getRect().w, title.getRect().h };
	title.setRect(renderQuad);
	for (int i = 0; i < 3; i++) {
		renderQuad = { WINDOW_WIDTH / 2 - buttons[i].getRect().w / 2, 350 + 70 * i, buttons[i].getRect().w, buttons[i].getRect().h};
		buttons[i].setRect(renderQuad);
		highlightedButtons[i].setRect(renderQuad);
	}
	currentButton = RETRY_NONE;
}

RetryScreen::~RetryScreen() {
	title.Free();
	for (int i = 0; i < 3; i++) {
		buttons[i].Free();
		highlightedButtons[i].Free();
	}
}

void RetryScreen::handleInput(bool& inStartScreen, bool& exitGame) {
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
				currentButton = RETRY_BUTTON;
			}
			else if (pointInsideRect(x, y, buttons[1].getRect())) {
				currentButton = RETURN_TO_MAIN_MENU_BUTTON;
			}
			else if (pointInsideRect(x, y, buttons[2].getRect())) {
				currentButton = RETRY_EXIT_BUTTON;
			}
			else {
				currentButton = RETRY_NONE;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (currentButton == RETRY_BUTTON) {
				inStartScreen = false;
				exitGame = false;
				tryAgain = true;
			}
			else if (currentButton == RETURN_TO_MAIN_MENU_BUTTON) {
				inStartScreen = true;
				exitGame = false;
				tryAgain = false;
			}
			else if (currentButton == RETRY_EXIT_BUTTON) {
				exitGame = true;
				inStartScreen = false;
				tryAgain = false;
			}
		}
	}
}

void RetryScreen::show(SDL_Renderer* screen) {
	SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
	SDL_RenderClear(screen);
	backGround.render(screen, NULL);
	title.render(screen, NULL);
	if (currentButton == RETRY_BUTTON) {
		highlightedButtons[0].render(screen, NULL);
	}
	else {
		buttons[0].render(screen, NULL);
	}
	if (currentButton == RETURN_TO_MAIN_MENU_BUTTON) {
		highlightedButtons[1].render(screen, NULL);
	}
	else {
		buttons[1].render(screen, NULL);
	}
	if (currentButton == RETRY_EXIT_BUTTON) {
		highlightedButtons[2].render(screen, NULL);
	}
	else {
		buttons[2].render(screen, NULL);
	}
	SDL_RenderPresent(screen);
}