#include "StartScreen.h"

StartScreen::StartScreen(SDL_Renderer* screen) {
	title.loadImage("images/StartScreen/title.png", screen);
	background.loadImage("images/StartScreen/background.png", screen);
	startButton.loadImage("images/StartScreen/startbutton.png", screen);
	settingsButton.loadImage("images/StartScreen/settingsbutton.png", screen);
	exitButton.loadImage("images/StartScreen/exitbutton.png", screen);
	highlightedStartButton.loadImage("images/StartScreen/highlightedStartButton.png", screen);
	highlightedExitButton.loadImage("images/StartScreen/highlightedExitButton.png", screen);
	highlightedSettingsButton.loadImage("images/StartScreen/highlightedSettingsButton.png", screen);
	startScreenMusic = Mix_LoadMUS("music/Pokemon Heart Gold.wav");

	background.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_Rect startButtonRect = startButton.getRect();
	startButtonRect = { WINDOW_WIDTH / 2 - startButtonRect.w / 2, WINDOW_HEIGHT * 2 / 3 - 30, startButtonRect.w, startButtonRect.h };
	startButton.setRect(startButtonRect);
	highlightedStartButton.setRect(startButtonRect);

	SDL_Rect settingsButtonRect = settingsButton.getRect();
	settingsButtonRect = { WINDOW_WIDTH / 2 - settingsButtonRect.w / 2, WINDOW_HEIGHT * 2 / 3 + 30, settingsButtonRect.w, settingsButtonRect.h };
	settingsButton.setRect(settingsButtonRect);
	highlightedSettingsButton.setRect(settingsButtonRect);

	SDL_Rect exitButtonRect = exitButton.getRect();
	exitButtonRect = { WINDOW_WIDTH / 2 - exitButtonRect.w / 2, WINDOW_HEIGHT * 2 / 3 + 90, exitButtonRect.w, exitButtonRect.h };
	exitButton.setRect(exitButtonRect);
	highlightedExitButton.setRect(exitButtonRect);
}

StartScreen::~StartScreen() {
	title.Free();
	background.Free();
	startButton.Free();
	exitButton.Free();
	highlightedStartButton.Free();
	highlightedExitButton.Free();
	Mix_FreeMusic(startScreenMusic);
}

void StartScreen::resetTitlePos() {
	SDL_Rect titleRect = title.getRect();
	SDL_Rect newTitleRect = { WINDOW_WIDTH / 2 - titleRect.w / 2, -titleRect.h, titleRect.w, titleRect.h };
	title.setRect(newTitleRect);
}

void StartScreen::show(SDL_Renderer* screen) {
	background.render(screen, NULL);
	title.render(screen, NULL);

	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(startScreenMusic, 0);
	}

	if (currentButton == START_BUTTON) {
		highlightedStartButton.render(screen, NULL);
	}
	else {
		startButton.render(screen, NULL);
	}
	
	if (currentButton == EXIT_BUTTON) {
		highlightedExitButton.render(screen, NULL);
	}
	else {
		exitButton.render(screen, NULL);
	}

	if (currentButton == SETTINGS_BUTTON) {
		highlightedSettingsButton.render(screen, NULL);
	}
	else {
		settingsButton.render(screen, NULL);
	}

	SDL_Rect titleRect = title.getRect();
	if (titleRect.y < 270) {
		titleRect.y += TITLE_FALL_SPEED;
		title.setRect(titleRect);
	}

	SDL_RenderPresent(screen);
}

void StartScreen::handleInput(SDL_Event& event, SDL_Window*& window, bool& inStartScreen, bool& gameOver) {
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				currentButton = START_BUTTON;
				break;
			case SDLK_DOWN:
				currentButton = EXIT_BUTTON;
				break;
			case SDLK_RETURN:
				if (currentButton == START_BUTTON) {
					inStartScreen = false;
					Mix_PauseMusic();
				}
				else if (currentButton == EXIT_BUTTON) {
					inStartScreen = false;
					gameOver = true;
					Mix_PauseMusic();
				}
				break;
			}
		}
		else if(event.type == SDL_MOUSEMOTION) {
			int x = event.motion.x;
			int y = event.motion.y;

			SDL_Rect temp = startButton.getRect();
			if (!(x > temp.x + temp.w || x < temp.x || y < temp.y || y > temp.y + temp.h)) {
				currentButton = START_BUTTON;
			}
			else {
				temp = exitButton.getRect();
				if (!(x > temp.x + temp.w || x < temp.x || y < temp.y || y > temp.y + temp.h)) {
					currentButton = EXIT_BUTTON;
				}
				else {
					temp = settingsButton.getRect();
					if (!(x > temp.x + temp.w || x < temp.x || y < temp.y || y > temp.y + temp.h)) {
						currentButton = SETTINGS_BUTTON;
					}
					else {
						currentButton = NONE;
					}
				}
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x = event.motion.x;
			int y = event.motion.y;

			SDL_Rect temp = startButton.getRect();
			if (!(x > temp.x + temp.w || x < temp.x || y < temp.y || y > temp.y + temp.h)) {
				inStartScreen = false;
				Mix_PauseMusic();
			}
			else {
				temp = exitButton.getRect();
				if (!(x > temp.x + temp.w || x < temp.x || y < temp.y || y > temp.y + temp.h)) {
					inStartScreen = false;
					gameOver = true;
					Mix_PauseMusic();
				}
			}
		}
		else if (event.type == SDL_QUIT) {

		}
	}
}