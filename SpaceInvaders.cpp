#include "BasicFunction.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyFormation.h"
#include "StartScreen.h"
#include "BackGroundMusic.h"
#include "AirCraftBoss.h"

BaseObject gBackGround;

void loadBackGround();


int main(int argc, char* argv[]) {

    init();

    loadBackGround();

    StartScreen startScreen(gScreen);

    BackGroundMusic music;

    startScreen.resetTitlePos();

    /*EnemyFormation testFormation(STACKED_FORMATION);
    testFormation.loadEnemies("images/Characters/enemy.png", gScreen);
    testFormation.loadProjectiles("images/Projectile/lazer.png", gScreen);*/

    Player mainChar(gScreen);

    AirCraftBoss testBoss(gScreen);

    bool gameOver = false;
    bool inStartScreen = true;

    SDL_WarpMouseInWindow(gWindow, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    SDL_ShowCursor(SDL_ENABLE);

    while (!gameOver) {

        if (inStartScreen) {

            startScreen.handleInput(gEvent, gWindow, inStartScreen, gameOver);

            startScreen.show(gScreen);

            if (!inStartScreen) {
                SDL_WarpMouseInWindow(gWindow, mainChar.getSpawnX(), mainChar.getSpawnY());
                SDL_ShowCursor(SDL_DISABLE);
            }
        }
        else {
            music.play();
            if (SDL_PollEvent(&gEvent) != 0) {
                if (gEvent.type == SDL_QUIT) {
                    gameOver = true;
                }

                if (mainChar.isAlive()) {
                    mainChar.handleInput(gEvent, gScreen, gWindow);
                }
            }

            SDL_SetRenderDrawColor(gScreen, 255, 0, 255, 255);
            SDL_RenderClear(gScreen);

            gBackGround.render(gScreen, NULL);

            mainChar.showProjectiles(gScreen);

            if (mainChar.isAlive()) {
                mainChar.show(gScreen);
                //testFormation.interactWithPlayer(mainChar);
                mainChar.hitAirCraftBoss(testBoss);
                mainChar.hitByAirCraftBoss(testBoss);
                mainChar.enemyContact(testBoss);
            }
            //testFormation.show(gScreen);
            if (testBoss.isAlive()) {
                testBoss.render(gScreen, NULL);
                testBoss.moveTowardsPlayer(mainChar.getHitBox());
                testBoss.shoot();
                testBoss.showProjectiles(gScreen);
            }
            SDL_RenderPresent(gScreen);

            //testFormation.moveFormation();
        }

        SDL_RenderPresent(gScreen);
           
    }

    quitSDL();


    return 0;
}

void init() {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) errorLog(std::cout, "SDL Init", true);

    gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_GRABBED);
    if (gWindow == NULL) errorLog(std::cout, "SDL Create Window", true);

    gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gScreen == NULL) errorLog(std::cout, "SDL Renderer", true);

    int imgFlag = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlag) & imgFlag)) std::cout << "IMG Init Error: " << IMG_GetError() << '\n';

    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << std::endl;
        exit(0);
    }

    if (Mix_Init(MIX_INIT_MP3) < 0) {
        std::cout << Mix_GetError() << std::endl;
    }

    SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(gScreen, WINDOW_WIDTH, WINDOW_HEIGHT);

    srand(time(NULL));


}

void loadBackGround() {
    bool check = gBackGround.loadImage("images/Background/sky.png", gScreen);
    if (!check) errorLog(std::cout, "Back ground render", true);
    gBackGround.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void quitSDL() {

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;


    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;

    Mix_CloseAudio();

    SDL_Quit();

}

