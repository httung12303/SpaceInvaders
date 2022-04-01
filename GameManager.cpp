#include "GameManager.h"

void GameManager::init() {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) errorLog(std::cout, "SDL Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_GRABBED);
    if (window == NULL) errorLog(std::cout, "SDL Create Window", true);

    screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (screen == NULL) errorLog(std::cout, "SDL Renderer", true);

    int imgFlag = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlag) & imgFlag)) std::cout << "IMG Init Error: " << IMG_GetError() << '\n';

    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << std::endl;
        exit(0);
    }

    if (Mix_Init(MIX_INIT_MP3) < 0) {
        std::cout << Mix_GetError() << std::endl;
    }

    SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(screen, WINDOW_WIDTH, WINDOW_HEIGHT);

    srand(time(NULL));
}

GameManager::~GameManager() {
	SDL_DestroyRenderer(screen);
	SDL_DestroyWindow(window);
    Mix_CloseAudio();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
    delete startScreen;
    delete settingsScreen;
    delete player;
    delete bossLevel;
    delete retryScreen;
    delete victoryScreen;
}

void GameManager::quit() {
    SDL_DestroyRenderer(screen);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

void GameManager::loadGame() {
    startScreen = new StartScreen(screen);
    settingsScreen = new SettingsScreen(screen);
    startScreen->resetTitlePos();
    retryScreen = new RetryScreen(screen);
    victoryScreen = new VictoryScreen(screen);
    mobLevel.push_back(new MobLevel(screen, WHEEL_FORMATION));
	mobLevel.push_back(new MobLevel(screen, STACKED_FORMATION));
    player = new Player(screen);
    music = new BackGroundMusic();
    bossLevel = new BossLevel(screen);
    BOSS_LEVEL = mobLevel.size();
    exitGame = false;
    inStartScreen = true;
    inSettingsScreen = false;
    musicPlaying = true;
	currentLevel = 0;
    SDL_WarpMouseInWindow(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void GameManager::run() {
    while (!exitGame) {
        if (inSettingsScreen) {
            settingsScreenProcess();
        }
        else if (inStartScreen) {
            startScreenProcess();
        }
        else {
            music->play(musicPlaying);
            if (!player->isAlive()) {
                retryScreenProcess();
                if (inStartScreen) {
                    Mix_HaltMusic();
                }
                continue;
            }
            else if ((currentLevel < BOSS_LEVEL && mobLevel[currentLevel]->mobLevelDefeated()) || bossLevel->bossDefeated()) {
                victoryScreenProcess();
                if (inStartScreen) {
                    Mix_HaltMusic();
                }
                continue;
            }
            SDL_ShowCursor(SDL_DISABLE);
            if (currentLevel == BOSS_LEVEL) {
                bossLevel->handleInput(event, *player, window, screen, inSettingsScreen, exitGame);
                bossLevel->process(*player, screen);
            } else {
				mobLevel[currentLevel]->handleInput(event, *player, window, screen, inSettingsScreen, exitGame);
				mobLevel[currentLevel]->process(*player, screen);
			}
            if (inSettingsScreen) {
                playerXPos = player->getXPos();
                playerYPos = player->getYPos();
            }
        }
    }
}

void GameManager::startScreenProcess() {
    SDL_ShowCursor(SDL_ENABLE);
    startScreen->playMusic(musicPlaying);
    startScreen->handleInput(event, window, inStartScreen, inSettingsScreen, exitGame);
    startScreen->show(screen);
    if (!inStartScreen) {
        SDL_WarpMouseInWindow(window, player->getSpawnX(), player->getSpawnY());
        player->reset();
        if (currentLevel == BOSS_LEVEL) {
            bossLevel->reset();
        } else {
			mobLevel[currentLevel]->reset();
		}
    }
    if (!inStartScreen || inSettingsScreen) {
        startScreen->resetTitlePos();
    }
}

void GameManager::settingsScreenProcess() {
    SDL_ShowCursor(SDL_ENABLE);
    if (inStartScreen) startScreen->playMusic(musicPlaying);
    else music->play(musicPlaying);
    settingsScreen->handleInput(inSettingsScreen, musicPlaying, exitGame);
    settingsScreen->show(screen, musicPlaying);
    if (!inSettingsScreen && !inStartScreen) {
        SDL_WarpMouseInWindow(window, playerXPos, playerYPos);
    }
}

void GameManager::retryScreenProcess() {
    SDL_ShowCursor(SDL_ENABLE);
    retryScreen->show(screen);
    retryScreen->handleInput(inStartScreen, exitGame);
    if (retryScreen->TryAgain()) {
        if (currentLevel == BOSS_LEVEL) {
            bossLevel->reset();
        }
        else {
            mobLevel[currentLevel]->reset();
        }
        player->reset();
        retryScreen->resetTryAgainOption();
        SDL_WarpMouseInWindow(window, player->getSpawnX(), player->getSpawnY());
    }
}

void GameManager::victoryScreenProcess() {
    SDL_ShowCursor(SDL_ENABLE);
    victoryScreen->show(screen, currentLevel == BOSS_LEVEL);
    victoryScreen->handleInput(inStartScreen, exitGame, currentLevel == BOSS_LEVEL);
    if (victoryScreen->playNextLevel() && currentLevel < BOSS_LEVEL) {
        currentLevel++;
        player->reset();
        if (currentLevel < BOSS_LEVEL) {
            mobLevel[currentLevel]->reset();
        } else {
			bossLevel->reset();
		}
        victoryScreen->resetNextLevelOption();
        SDL_WarpMouseInWindow(window, player->getSpawnX(), player->getSpawnY());
    } else if(victoryScreen->restartGame() && currentLevel == BOSS_LEVEL) {
		currentLevel = 0;
		player->reset();
		bossLevel->reset();
		victoryScreen->resetRestartOption();
		SDL_WarpMouseInWindow(window, player->getSpawnX(), player->getSpawnY());
	}
    else if (victoryScreen->replayBossLevel() && currentLevel == BOSS_LEVEL) {
        player->reset();
        bossLevel->reset();
        victoryScreen->resetReplayBossOption();
        SDL_WarpMouseInWindow(window, player->getSpawnX(), player->getSpawnY());
    }
}