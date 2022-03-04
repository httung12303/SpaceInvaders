#include "BasicFunction.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"

BaseObject gBackGround;

void initData();

void loadBackGround();

void waitUntilKeyPressed();

void errorLog(std::ostream& os, std::string msg, bool fatal);

void quitSDL();

int main(int argc, char* argv[]) {

    initData();

    loadBackGround();

    Player mainChar;
    mainChar.loadImage("images/Characters/planeIII.png", gScreen);
    mainChar.setClip();
    mainChar.resetPos();
    mainChar.loadProjectile("images/Projectile/projectile2.png", gScreen);

    Enemy testEnemy;

    testEnemy.loadImage("images/Characters/enemy.png", gScreen);
    testEnemy.setClip();
    testEnemy.setPos(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    bool gameOver = false;

    while (!gameOver) {

        if (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) {
                gameOver = true;
            }

            if (mainChar.isAlive()) {
                mainChar.handleInput(gEvent, gScreen);
            }
        }


        SDL_SetRenderDrawColor(gScreen, 255, 0, 255, 255);
        SDL_RenderClear(gScreen);

        gBackGround.render(gScreen, NULL);

        if (testEnemy.isAlive()) {
            testEnemy.show(gScreen);
            mainChar.hitEnemy(testEnemy);
        }

        if (mainChar.isAlive()) {
            mainChar.show(gScreen);
        }

        mainChar.showProjectiles(gScreen);

        SDL_RenderPresent(gScreen);

        SDL_Delay(100);
    }


    quitSDL();


    return 0;
}

void initData() {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) errorLog(std::cout, "SDL Init", true);

    gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) errorLog(std::cout, "SDL Create Window", true);

    gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gScreen == NULL) errorLog(std::cout, "SDL Renderer", true);

    int imgFlag = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlag) & imgFlag)) std::cout << "IMG Init Error: " << IMG_GetError() << '\n';

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

void waitUntilKeyPressed()
{
    SDL_Event e;

    while (true) {
        if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }

}

void errorLog(std::ostream& os, std::string msg, bool fatal) {

    os << msg << " Error: " << SDL_GetError() << '\n';

    if (fatal) {
        SDL_Quit();
        exit(1);
    }

}

void quitSDL() {

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;


    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;

    SDL_Quit();

}

