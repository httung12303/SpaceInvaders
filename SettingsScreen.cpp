#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(SDL_Renderer* screen) {
	title.loadImage("images/SettingsScreen/Settings.png", screen);
	backGround.loadImage("images/Background/sky.png", screen);
	backGround.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	musicOn.loadImage("images/SettingsScreen/MusicOn.png", screen);
	musicOff.loadImage("images/SettingsScreen/MusicOff.png", screen);
	exitButton.loadImage("images/SettingsScreen/exitbutton.png", screen);
	returnButton.loadImage("images/SettingsScreen/Return.png", screen);
	highlightedMusicOn.loadImage("images/SettingsScreen/HighlightedMusicOn.png", screen);
	highlightedMusicOff.loadImage("images/SettingsScreen/HighlightedMusicOff.png", screen);	
	highlightedExitButton.loadImage("images/SettingsScreen/highlightedExitButton.png", screen);
	highlightedReturnButton.loadImage("images/SettingsScreen/HighlightedReturn.png", screen);
	
	SDL_Rect renderQuad = { WINDOW_WIDTH / 2 - title.getRect().w / 2, 150, title.getRect().w, title.getRect().h };
	title.setRect(renderQuad);
	
	renderQuad = { WINDOW_WIDTH / 2 - musicOn.getRect().w / 2, 300, musicOn.getRect().w, musicOn.getRect().h };
	musicOn.setRect(renderQuad);
	highlightedMusicOn.setRect(renderQuad);
	
	renderQuad = { WINDOW_WIDTH / 2 - musicOn.getRect().w / 2, 300, musicOff.getRect().w, musicOff.getRect().h };
	musicOff.setRect(renderQuad);
	highlightedMusicOff.setRect(renderQuad);
	
	renderQuad = { WINDOW_WIDTH / 2 - exitButton.getRect().w / 2, 400, exitButton.getRect().w, exitButton.getRect().h };
	exitButton.setRect(renderQuad);
	highlightedExitButton.setRect(renderQuad);
	
	renderQuad = { WINDOW_WIDTH / 2 - returnButton.getRect().w / 2, 500, returnButton.getRect().w, returnButton.getRect().h };
	returnButton.setRect(renderQuad);
	highlightedReturnButton.setRect(renderQuad);
	
}

SettingsScreen::~SettingsScreen() {
	backGround.Free();
	musicOn.Free();
	musicOff.Free();
	exitButton.Free();
	returnButton.Free();
	highlightedMusicOn.Free();
	highlightedMusicOff.Free();
	highlightedExitButton.Free();
	highlightedReturnButton.Free();
}

void SettingsScreen::handleInput(bool& inSettingsScreen, bool& musicPlaying, bool& exitGame) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exitGame = true;
			inSettingsScreen = false;
			break;
		case SDL_MOUSEMOTION:
			if (pointInsideRect(event.motion.x, event.motion.y, musicOn.getRect()))
				currentButton = SETTINGS_MUSIC_ON_BUTTON;
			else if (pointInsideRect(event.motion.x, event.motion.y, exitButton.getRect()))
				currentButton = SETTINGS_EXIT_BUTTON;
			else if (pointInsideRect(event.motion.x, event.motion.y, returnButton.getRect()))
				currentButton = SETTINGS_RETURN_BUTTON;
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
			break;
		}
	}
}

void SettingsScreen::show(SDL_Renderer* screen, const bool& musicPlaying) {
	SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
	SDL_RenderPresent(screen);
	backGround.render(screen);
	title.render(screen);
	if (musicPlaying) {
		if(currentButton == SETTINGS_MUSIC_ON_BUTTON)
			highlightedMusicOn.render(screen);
		else
			musicOn.render(screen);
	}
	else {
		if (currentButton == SETTINGS_MUSIC_ON_BUTTON)
			highlightedMusicOff.render(screen);
		else
			musicOff.render(screen);
	}
	if (currentButton == SETTINGS_EXIT_BUTTON)
		highlightedExitButton.render(screen);
	else
		exitButton.render(screen);
	if (currentButton == SETTINGS_RETURN_BUTTON)
		highlightedReturnButton.render(screen);
	else
		returnButton.render(screen);
	
	SDL_RenderPresent(screen);
}