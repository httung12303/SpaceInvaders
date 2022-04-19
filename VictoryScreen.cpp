#include "VictoryScreen.h"

VictoryScreen::VictoryScreen(SDL_Renderer* screen) {
	title.loadImage("images/VictoryScreen/Title.png", screen);
	buttons[0].loadImage("images/VictoryScreen/NextLevel.png", screen);
	buttons[1].loadImage("images/VictoryScreen/Return.png", screen);
	buttons[2].loadImage("images/VictoryScreen/Exit.png", screen);
	buttons[3].loadImage("images/VictoryScreen/Restart.png", screen);
	buttons[4].loadImage("images/VictoryScreen/ReplayBossLevel.png", screen);
	highlightedButtons[0].loadImage("images/VictoryScreen/highlightedNextLevel.png", screen);
	highlightedButtons[1].loadImage("images/VictoryScreen/highlightedReturn.png", screen);
	highlightedButtons[2].loadImage("images/VictoryScreen/highlightedExit.png", screen);
	highlightedButtons[3].loadImage("images/VictoryScreen/highlightedRestart.png", screen);
	highlightedButtons[4].loadImage("images/VictoryScreen/highlightedReplayBossLevel.png", screen);
	backGround.loadImage(GALAXY_BACKGROUND_PATH, screen);
	backGround.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Rect renderQuad = { WINDOW_WIDTH / 2 - title.getRect().w / 2, 150, title.getRect().w, title.getRect().h };
	title.setRect(renderQuad);
	renderQuad = { WINDOW_WIDTH / 2 - buttons[3].getRect().w / 2, 350, buttons[3].getRect().w, buttons[3].getRect().h };
	buttons[3].setRect(renderQuad);
	highlightedButtons[3].setRect(renderQuad);
	renderQuad = { WINDOW_WIDTH / 2 - buttons[4].getRect().w / 2, 280, buttons[4].getRect().w, buttons[4].getRect().h };
	buttons[4].setRect(renderQuad);
	highlightedButtons[4].setRect(renderQuad);
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
	else {
		if (currentButton == NEXT_LEVEL_BUTTON || currentButton == VICTORY_RESTART) {
			highlightedButtons[3].render(screen, NULL);
		}
		else {
			buttons[3].render(screen, NULL);
		}
		if (currentButton == VICTORY_REPLAY_BOSS_LEVEL) {
			highlightedButtons[4].render(screen, NULL);
		}
		else {
			buttons[4].render(screen, NULL);
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

void VictoryScreen::handleInput(bool& inStartScreen, bool& exitGame, bool bossLevel) {
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
			else if (pointInsideRect(x, y, buttons[3].getRect())) {
				currentButton = VICTORY_RESTART;
			}
			else if(pointInsideRect(x, y, buttons[4].getRect())) {
				currentButton = VICTORY_REPLAY_BOSS_LEVEL;
			}
			else {
				currentButton = VICTORY_NONE;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if ((currentButton == NEXT_LEVEL_BUTTON || currentButton == VICTORY_RESTART) && bossLevel) {
				inStartScreen = false;
				exitGame = false;
				restart = true;
			}
			else if (currentButton == VICTORY_REPLAY_BOSS_LEVEL && bossLevel) {
				inStartScreen = false;
				exitGame = false;
				replayBoss = true;
			}
			else if (currentButton == NEXT_LEVEL_BUTTON && !bossLevel) {
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