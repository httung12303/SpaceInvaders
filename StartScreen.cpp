#include "StartScreen.h"

StartScreen::StartScreen(SDL_Renderer* screen) {
	title.loadImage("images/StartScreen/title.png", screen);
	background.loadImage("images/StartScreen/background.png", screen);
	buttons[0].loadImage("images/StartScreen/startbutton.png", screen);
	buttons[1].loadImage("images/StartScreen/settingsbutton.png", screen);
	buttons[2].loadImage("images/StartScreen/exitbutton.png", screen);
	highlightedButtons[0].loadImage("images/StartScreen/highlightedStartButton.png", screen);
	highlightedButtons[2].loadImage("images/StartScreen/highlightedExitButton.png", screen);
	highlightedButtons[1].loadImage("images/StartScreen/highlightedSettingsButton.png", screen);
	startScreenMusic = Mix_LoadMUS("music/Pokemon Heart Gold.wav");

	background.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_Rect startButtonRect = buttons[0].getRect();
	startButtonRect = { WINDOW_WIDTH / 2 - startButtonRect.w / 2, WINDOW_HEIGHT * 2 / 3 - 30, startButtonRect.w, startButtonRect.h };
	buttons[0].setRect(startButtonRect);
	highlightedButtons[0].setRect(startButtonRect);

	SDL_Rect settingsButtonRect = buttons[1].getRect();
	settingsButtonRect = { WINDOW_WIDTH / 2 - settingsButtonRect.w / 2, WINDOW_HEIGHT * 2 / 3 + 25, settingsButtonRect.w, settingsButtonRect.h };
	buttons[1].setRect(settingsButtonRect);
	highlightedButtons[1].setRect(settingsButtonRect);

	SDL_Rect exitButtonRect = buttons[2].getRect();
	exitButtonRect = { WINDOW_WIDTH / 2 - exitButtonRect.w / 2, WINDOW_HEIGHT * 2 / 3 + 80, exitButtonRect.w, exitButtonRect.h };
	buttons[2].setRect(exitButtonRect);
	highlightedButtons[2].setRect(exitButtonRect);
}

StartScreen::~StartScreen() {
	title.Free();
	background.Free();
	for(int i = 0; i < 3; i++) {
		buttons[i].Free();
		highlightedButtons[i].Free();
	}
	Mix_FreeMusic(startScreenMusic);
}

void StartScreen::resetTitlePos() {
	SDL_Rect titleRect = title.getRect();
	SDL_Rect newTitleRect = { WINDOW_WIDTH / 2 - titleRect.w / 2, -titleRect.h, titleRect.w, titleRect.h };
	title.setRect(newTitleRect);
}

void StartScreen::playMusic(const bool& musicPlaying) {
	if (musicPlaying) {
		if (Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(startScreenMusic, 0);
		}
		if (Mix_PausedMusic()) {
			Mix_ResumeMusic();
		}
	}
	else {
		if (!Mix_PausedMusic()) {
			Mix_PauseMusic();
		}
	}
}

void StartScreen::show(SDL_Renderer* screen) {
	background.render(screen, NULL);
	title.render(screen, NULL);

	if (currentButton == START_BUTTON) {
		highlightedButtons[0].render(screen, NULL);
	}
	else {
		buttons[0].render(screen, NULL);
	}
	
	if (currentButton == EXIT_BUTTON) {
		highlightedButtons[2].render(screen, NULL);
	}
	else {
		buttons[2].render(screen, NULL);
	}

	if (currentButton == SETTINGS_BUTTON) {
		highlightedButtons[1].render(screen, NULL);
	}
	else {
		buttons[1].render(screen, NULL);
	}

	SDL_Rect titleRect = title.getRect();
	if (titleRect.y < 270) {
		titleRect.y += TITLE_FALL_SPEED;
		title.setRect(titleRect);
	}

	SDL_RenderPresent(screen);
}

void StartScreen::handleInput(SDL_Event& event, SDL_Window*& window, bool& inStartScreen, bool& inSettingsScreen, bool& gameOver) {
	while (SDL_PollEvent(&event) != 0) {
		if(event.type == SDL_MOUSEMOTION) {
			int x = event.motion.x;
			int y = event.motion.y;
			currentButton = NONE;
			SDL_Rect temp = buttons[0].getRect();
			if (pointInsideRect(x, y, temp)) {
				currentButton = START_BUTTON;
			}
			temp = buttons[2].getRect();
			if (pointInsideRect(x, y, temp)) {
				currentButton = EXIT_BUTTON;
			}
			temp = buttons[1].getRect();
			if (pointInsideRect(x, y, temp)) {
				currentButton = SETTINGS_BUTTON;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x = event.motion.x;
			int y = event.motion.y;

			if (pointInsideRect(x, y, buttons[0].getRect())) {
				inStartScreen = false;
			}
			else if(pointInsideRect(x, y, buttons[2].getRect())) {
				inStartScreen = false;
				gameOver = true;
			}
			else if (pointInsideRect(x, y, buttons[1].getRect())) {
				inSettingsScreen = true;
			}
		}
		else if (event.type == SDL_QUIT) {
			gameOver = true;
		}
	}

	if (!inStartScreen) {
		Mix_HaltMusic();
	}

}