#include "BossLevel.h"

BossLevel::BossLevel(SDL_Renderer* screen) : Level(screen) {
	boss = new AirCraftBoss(screen);
	backGround.loadImage(GALAXY_BACKGROUND_PATH, screen);
	backGround.setRectSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

BossLevel::~BossLevel() {
	delete boss;
    backGround.Free();
}

void BossLevel::process(Player& player, SDL_Renderer* screen) {
    SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
    SDL_RenderClear(screen);
	backGround.render(screen);
    renderPowerUps(screen);
    if (player.isAlive()) {
        player.show(screen);
        //testFormation.interactWithPlayer(mainChar);
        player.hitAirCraftBoss(*boss);
        player.hitByAirCraftBoss(*boss);
        player.enemyContact(*boss);
        playerPowerUp(player);
    }
    //testFormation.show(gScreen);
    if (boss->isAlive()) {
        boss->render(screen, NULL);
        boss->moveTowardsPlayer(player.getHitBox());
        boss->shoot();
        boss->showProjectiles(screen, player.getHitBox());
        boss->showHPBar(screen);
    }
    player.showProjectiles(screen);
    SDL_RenderPresent(screen);
    movePowerUps();
    insertRandomPowerUp();
}

void BossLevel::handleInput(SDL_Event& event, Player& player, SDL_Window* window, SDL_Renderer* screen, bool& inSettingsScreen, bool& exitGame) {
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            exitGame = true;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            inSettingsScreen = true;
        }
        if (player.isAlive()) {
            player.handleInput(event, screen, window);
        }
    }
}