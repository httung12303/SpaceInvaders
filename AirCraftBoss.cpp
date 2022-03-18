#include "AirCraftBoss.h"

AirCraftBoss::AirCraftBoss(SDL_Renderer* screen) {
	if (!loadImage("images/Characters/BossPRVW.png", screen)) {
		errorLog(std::cout, "Loading AirCraftBoss Image", true);
		exit(1);
	}
	setRect(WINDOW_WIDTH / 2 - this->getRect().w / 2, 0);
	targetCenter = WINDOW_WIDTH / 2 - this->getRect().w / 2;
	alive = 1;
	hp = MAX_BOSS_HP;
}

AirCraftBoss::~AirCraftBoss() {

}

void AirCraftBoss::show(SDL_Renderer* screen) {
	render(screen, NULL);
}

void AirCraftBoss::moveTowardsPlayer(const SDL_Rect& playerHitbox) {
	int playerCenter = playerHitbox.x + playerHitbox.w / 2;
	int bossCenter = this->getRect().x + this->getRect().w / 2;
	unsigned int curMove = SDL_GetTicks();
	if (curMove - lastMove >= 3000) {
		targetCenter = playerCenter;
		lastMove = curMove;
	}
	if (bossCenter > playerCenter && bossCenter - playerCenter >= BOSS_SPEED) {
		setRect(this->getRect().x - BOSS_SPEED, this->getRect().y);
	}
	else if (bossCenter < playerCenter && bossCenter - playerCenter <= -BOSS_SPEED) {
		setRect(this->getRect().x + BOSS_SPEED, this->getRect().y);
	}
}