#include "MobLevel.h"

MobLevel::MobLevel(SDL_Renderer* screen, const std::string& formationPath) {
	enemyFormation = new EnemyFormation(formationPath);
	enemyFormation->loadEnemies("images/Characters/enemy.png", screen);
	enemyFormation->loadProjectiles("images/Projectile/lazer.png", screen);
	backGround.loadImage("images/Background/sky.png", screen);
	backGround.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

MobLevel::~MobLevel() {
    backGround.Free();
	delete enemyFormation;
}

void MobLevel::handleInput(SDL_Event& event, Player& player, SDL_Window* window, SDL_Renderer* screen, bool& exitGame) {
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            exitGame = true;
        }
        if (player.isAlive()) {
            player.handleInput(event, screen, window);
        }
    }
}

void MobLevel::process(Player& player, SDL_Renderer* screen) {
    SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
    SDL_RenderClear(screen);
    backGround.render(screen);
    if (player.isAlive()) {
        enemyFormation->interactWithPlayer(player);
        player.show(screen);
    }
    enemyFormation->show(screen);
    player.showProjectiles(screen);
    SDL_RenderPresent(screen);
    enemyFormation->moveFormation();
}