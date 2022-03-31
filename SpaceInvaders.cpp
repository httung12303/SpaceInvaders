#include "GameManager.h"


int main(int argc, char* argv[]) {
    GameManager game;
    game.init();
    game.loadGame();
    game.run();
    game.quit();

    return 0;
}

