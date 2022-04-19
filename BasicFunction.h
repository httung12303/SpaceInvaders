#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_audio.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fstream>
#include <ctime>
#include <vector>
#include <fstream>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;



const int WINDOW_WIDTH = 1140;
const int WINDOW_HEIGHT = 720;
const std::string WINDOW_TITLE = "Space Invaders";

const std::string STACKED_FORMATION = "formations/StackedRows.txt";
const std::string WHEEL_FORMATION = "formations/Wheel.txt";

const int COLOR_KEY_RED = 167;
const int COLOR_KEY_GREEN = 175;
const int COLOR_KEY_BLUE = 180;

const int PLAYER_HORIZONTAL_SPEED = 24;
const int PLAYER_VERTICAL_SPEED = 24;

const int ENEMY_HORIZONTAL_SPEED = 60;
const int ENEMY_VERTICAL_SPEED = 60;

const int PLAYER_PROJ_SPEED = 5;
const int ENEMY_STANDARD_PROJ_SPEED = 3;
const int BOSS_ORB_SPEED = 5;
const int BOSS_HOMING_MISSILE_SPEED = 2;
const int BOSS_SPEED = 2;

const int PLAYER_ANIMATION_COUNT = 25;
const int ENEMY_ANIMATION_COUNT = 8;

const int IDLE = 0;
const int MOVE_RIGHT = 1;
const int MOVE_LEFT = 2;
const int MOVE_UP = 1;
const int MOVE_DOWN = 2;

const std::string SKY_BACKGROUND_PATH = "images/Background/sky.png";
const std::string GALAXY_BACKGROUND_PATH = "images/Background/galaxy.png";
const std::string GALAXY_2_BACKGROUND_PATH = "images/Background/galaxy2.png";

void waitUntilKeyPressed();

void errorLog(std::ostream& os, std::string msg, bool fatal);

bool overlap(const SDL_Rect& a, const SDL_Rect& b);

bool pointInsideRect(const int& x, const int& y, const SDL_Rect rect);

const unsigned int FRAME_DELAY = 100;

