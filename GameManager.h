#pragma once
#include "BasicFunction.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyFormation.h"
#include "StartScreen.h"
#include "BackGroundMusic.h"
#include "AirCraftBoss.h"
#include "BossLevel.h"
#include "MobLevel.h"
#include "SettingsScreen.h"
#include "RetryScreen.h"
#include "VictoryScreen.h"
#include "Level.h"
#include "ControlsScreen.h"

class GameManager {
public:
    ~GameManager();
    void init();
    void loadGame();
    void run();
    void quit();
    void startScreenProcess();
	void settingsScreenProcess();
	void retryScreenProcess();
    void victoryScreenProcess();
    void controlsScreenProcess();
private:
    SDL_Window* window = NULL;
	SDL_Renderer* screen = NULL;
	SDL_Event event;
	
    StartScreen* startScreen = NULL;
    SettingsScreen* settingsScreen = NULL;
    RetryScreen* retryScreen = NULL;
    VictoryScreen* victoryScreen = NULL;
    BackGroundMusic* music = NULL;
    ControlsScreen* controlsScreen = NULL;
    std::vector<Level*> levels;
    Player* player = NULL;
	
    bool playing;
    bool exitGame;
    bool inStartScreen;
    bool inSettingsScreen;
    bool inControlsScreen;
    bool musicPlaying;
    float playerXPos;
    float playerYPos;
    int currentLevel;
    int BOSS_LEVEL;
};