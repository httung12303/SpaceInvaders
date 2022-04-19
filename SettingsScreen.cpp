#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(SDL_Renderer* screen) {
	title.loadImage("images/SettingsScreen/Settings.png", screen);
	backGround.loadImage(GALAXY_BACKGROUND_PATH, screen);
	backGround.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	buttons[0].loadImage("images/SettingsScreen/MusicOn.png", screen);
	buttons[1].loadImage("images/SettingsScreen/MusicOff.png", screen);
	buttons[2].loadImage("images/SettingsScreen/exitbutton.png", screen);
	buttons[3].loadImage("images/SettingsScreen/Return.png", screen);
	buttons[4].loadImage("images/SettingsScreen/ReturnToMenu.png", screen);
	buttons[5].loadImage("images/SettingsScreen/Retry.png", screen);
	highlightedButtons[0].loadImage("images/SettingsScreen/HighlightedMusicOn.png", screen);
	highlightedButtons[1].loadImage("images/SettingsScreen/HighlightedMusicOff.png", screen);
	highlightedButtons[2].loadImage("images/SettingsScreen/highlightedExitButton.png", screen);
	highlightedButtons[3].loadImage("images/SettingsScreen/HighlightedReturn.png", screen);
	highlightedButtons[4].loadImage("images/SettingsScreen/HighlightedReturnToMenu.png", screen);
	highlightedButtons[5].loadImage("images/SettingsScreen/highlightedRetry.png", screen);
	
	SDL_Rect renderQuad = { WINDOW_WIDTH / 2 - title.getRect().w / 2, 150, title.getRect().w, title.getRect().h };
	title.setRect(renderQuad);

	renderQuad = { WINDOW_WIDTH / 2 - buttons[0].getRect().w / 2, 350, buttons[0].getRect().w, buttons[0].getRect().h };
	buttons[0].setRect(renderQuad);
	highlightedButtons[0].setRect(renderQuad);

	renderQuad = { WINDOW_WIDTH / 2 - buttons[1].getRect().w / 2, 350, buttons[1].getRect().w, buttons[1].getRect().h };
	buttons[1].setRect(renderQuad);
	highlightedButtons[1].setRect(renderQuad);

	renderQuad = { WINDOW_WIDTH / 2 - buttons[4].getRect().w / 2, 400, buttons[4].getRect().w, buttons[4].getRect().h };
	buttons[4].setRect(renderQuad);
	highlightedButtons[4].setRect(renderQuad);

	renderQuad = { WINDOW_WIDTH / 2 - buttons[3].getRect().w / 2, 450, buttons[3].getRect().w, buttons[3].getRect().h };
	buttons[3].setRect(renderQuad);
	highlightedButtons[3].setRect(renderQuad);

	renderQuad = { WINDOW_WIDTH / 2 - buttons[2].getRect().w / 2, 500, buttons[2].getRect().w, buttons[2].getRect().h };
	buttons[2].setRect(renderQuad);
	highlightedButtons[2].setRect(renderQuad);

	renderQuad = {WINDOW_WIDTH / 2 - buttons[5].getRect().w / 2, 300, buttons[5].getRect().w, buttons[5].getRect().h };
	buttons[5].setRect(renderQuad);
	highlightedButtons[5].setRect(renderQuad);
	
	currentButton = SETTINGS_NONE;
}

SettingsScreen::~SettingsScreen() {
	backGround.Free();
	for (int i = 0; i < 5; i++) {
		buttons[i].Free();
		highlightedButtons[i].Free();
	}
}

void SettingsScreen::handleInput(bool& inStartScreen, bool& inSettingsScreen, bool& musicPlaying, bool& exitGame, Player*& player, Level*& level, const bool& playing) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exitGame = true;
			inSettingsScreen = false;
			break;
		case SDL_MOUSEMOTION:
			if (pointInsideRect(event.motion.x, event.motion.y, buttons[0].getRect()))
				currentButton = SETTINGS_MUSIC_ON_BUTTON;
			else if (pointInsideRect(event.motion.x, event.motion.y, buttons[2].getRect()))
				currentButton = SETTINGS_EXIT_BUTTON;
			else if (pointInsideRect(event.motion.x, event.motion.y, buttons[3].getRect()))
				currentButton = SETTINGS_RETURN_BUTTON;
			else if (pointInsideRect(event.motion.x, event.motion.y, buttons[4].getRect()))
				currentButton = SETTINGS_RETURN_TO_MENU_BUTTON;
			else if (pointInsideRect(event.motion.x, event.motion.y, buttons[5].getRect()) && playing)
				currentButton = SETTINGS_RETRY;
			else
				currentButton = SETTINGS_NONE;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (currentButton == SETTINGS_MUSIC_ON_BUTTON && musicPlaying)
				musicPlaying = false;
			else if (currentButton == SETTINGS_MUSIC_ON_BUTTON && !musicPlaying)
				musicPlaying = true;
			else if (currentButton == SETTINGS_EXIT_BUTTON)
				exitGame = true;
			else if (currentButton == SETTINGS_RETURN_BUTTON)
				inSettingsScreen = false;
			else if (currentButton == SETTINGS_RETURN_TO_MENU_BUTTON) {
				inStartScreen = true;
				inSettingsScreen = false;
			}
			else if (currentButton == SETTINGS_RETRY && playing) {
				inSettingsScreen = false;
				player->reset();
				level->reset();
			}
			break;
		}
	}
}

void SettingsScreen::show(SDL_Renderer* screen, const bool& musicPlaying, const bool& playing) {
	SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
	SDL_RenderPresent(screen);
	backGround.render(screen);
	title.render(screen);
	if (musicPlaying) {
		if(currentButton == SETTINGS_MUSIC_ON_BUTTON)
			highlightedButtons[0].render(screen);
		else
			buttons[0].render(screen);
	}
	else {
		if (currentButton == SETTINGS_MUSIC_ON_BUTTON)
			highlightedButtons[1].render(screen);
		else
			buttons[1].render(screen);
	}
	if (currentButton == SETTINGS_EXIT_BUTTON)
		highlightedButtons[2].render(screen);
	else
		buttons[2].render(screen);
	if (currentButton == SETTINGS_RETURN_BUTTON)
		highlightedButtons[3].render(screen);
	else
		buttons[3].render(screen);

	if (currentButton == SETTINGS_RETURN_TO_MENU_BUTTON)
		highlightedButtons[4].render(screen);
	else
		buttons[4].render(screen);

	if (currentButton == SETTINGS_RETRY && playing)
		highlightedButtons[5].render(screen);
	else if (playing)
		buttons[5].render(screen);
	
	SDL_RenderPresent(screen);
}