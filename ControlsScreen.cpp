#include "ControlsScreen.h"

ControlsScreen::ControlsScreen(SDL_Renderer* screen) {
	screenTemplate.loadImage("images/ControlsScreen/ControlsScreen.png", screen);
	screenTemplate.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	buttons[0].loadImage("images/ControlsScreen/Return.png", screen);
	buttons[1].loadImage("images/ControlsScreen/HighlightedReturn.png", screen);
	SDL_Rect rect = { WINDOW_WIDTH / 2 - buttons[0].getRect().w / 2, WINDOW_HEIGHT / 10 * 9 - buttons[0].getRect().h / 2, buttons[0].getRect().w, buttons[0].getRect().h };
	buttons[0].setRect(rect);
	buttons[1].setRect(rect);
	currentButton = NONE;
}

ControlsScreen::~ControlsScreen() {
	screenTemplate.Free();
	buttons[0].Free();
	buttons[1].Free();
}

void ControlsScreen::handleInput(bool& inControlsScreen, bool& inSettingsScreen, bool& exitGame) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			inControlsScreen = false;
			inSettingsScreen = false;
			exitGame = true;
		}
		else if (event.type == SDL_MOUSEMOTION) {
			if (pointInsideRect(event.motion.x, event.motion.y, buttons[0].getRect())) {
				currentButton = RETURN_BUTTON;
			}
			else {
				currentButton = NONE;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (currentButton == RETURN_BUTTON) {
				inControlsScreen = false;
				inSettingsScreen = true;
			}
		}
	}
}

void ControlsScreen::show(SDL_Renderer* screen) {
	SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
	SDL_RenderPresent(screen);
	screenTemplate.render(screen);
	if (currentButton == RETURN_BUTTON) {
		buttons[1].render(screen);
	}
	else {
		buttons[0].render(screen);
	}
	SDL_RenderPresent(screen);
}