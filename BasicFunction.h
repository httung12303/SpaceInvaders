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

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;


const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;
const std::string WINDOW_TITLE = "My Game";

const int COLOR_KEY_RED = 167;
const int COLOR_KEY_GREEN = 175;
const int COLOR_KEY_BLUE = 180;

const int PLAYER_HORIZONTAL_SPEED = 24;
const int PLAYER_VERTICAL_SPEED = 24;

const int ENEMY_HORIZONTAL_SPEED = 60;
const int ENEMY_VERTICAL_SPEED = 60;

const int PLAYER_PROJ_SPEED = 5;
const int ENEMY_PROJ_SPEED = 6;

const int PLAYER_ANIMATION_COUNT = 25;
const int ENEMY_ANIMATION_COUNT = 8;

const int IDLE = 0;
const int MOVE_RIGHT = 1;
const int MOVE_LEFT = 2;
const int MOVE_UP = 1;
const int MOVE_DOWN = 2;

void initData();

void loadBackGround();

void waitUntilKeyPressed();

void errorLog(std::ostream& os, std::string msg, bool fatal);

void quitSDL();

const unsigned int FRAME_DELAY = 100;

