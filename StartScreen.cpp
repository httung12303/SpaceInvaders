#include "StartScreen.h"

StartScreen::StartScreen(SDL_Renderer* screen) {
	title.loadImage("images/StartScreen/title.png", screen);
	background.loadImage("images/StartScreen/background.png", screen);
}

StartScreen::~StartScreen() {

}

void StartScreen::resetTitlePos() {
	SDL_Rect titleRect = title.getRect();
	SDL_Rect newTitleRect = { WINDOW_WIDTH / 2 - titleRect.w / 2, -titleRect.h, titleRect.w, titleRect.h };
	title.setRect(newTitleRect);
}

void StartScreen::show(SDL_Renderer* screen) {
	background.render(screen, NULL);
	title.render(screen, NULL);
	SDL_Rect titleRect = title.getRect();
	if (titleRect.y < 260) {
		titleRect.y += TITLE_FALL_SPEED;
		title.setRect(titleRect);
	}
}