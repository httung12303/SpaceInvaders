#include "AirCraftBoss.h"
#include "cmath"
#include <cstdlib>

AirCraftBoss::AirCraftBoss(SDL_Renderer* screen) {
	if (!loadImage("images/Characters/BossPRVW.png", screen)) {
		errorLog(std::cout, "Loading AirCraftBoss Image", true);
		exit(1);
	}
	standardProjectile.loadImage("images/Projectile/lazer.png", screen);
	orb.loadImage("images/Projectile/redorb.png", screen);
	setRect(WINDOW_WIDTH / 2 - this->getRect().w / 2, 0);
	targetCenter = WINDOW_WIDTH / 2 - this->getRect().w / 2;
	alive = 1;
	hp = MAX_BOSS_HP;
	lastOrbCircle = 0;
}

AirCraftBoss::~AirCraftBoss() {

}

void AirCraftBoss::moveTowardsPlayer(const SDL_Rect& playerHitbox) {
	int playerCenter = playerHitbox.x + playerHitbox.w / 2;
	int bossCenter = this->getRect().x + this->getRect().w / 2;
	unsigned int curMove = SDL_GetTicks();
	if (curMove - lastMove >= 500) {
		targetCenter = playerCenter;
		lastMove = curMove;
	}
	if (bossCenter > targetCenter && bossCenter - targetCenter >= BOSS_SPEED) {
		setRect(this->getRect().x - BOSS_SPEED, this->getRect().y);
	}
	else if (bossCenter < targetCenter && bossCenter - targetCenter <= -BOSS_SPEED) {
		setRect(this->getRect().x + BOSS_SPEED, this->getRect().y);
	}
}

void AirCraftBoss::shoot() {
	unsigned int curShot = SDL_GetTicks();
	if (curShot > lastStandardShot + 1000) {
		if (tripleStandardHit != 3) {
			SDL_Rect temp = standardProjectile.getRect();
			SDL_Rect bossRect = this->getRect();
			SDL_Rect projRect;
			projRect = { bossRect.x + 20, this->getRect().y + this->getRect().h - temp.h / 2 - 150, temp.w, temp.h };
			enemiesStandardProjectile.push_back(projRect);
			projRect = { bossRect.x + bossRect.w - temp.w - 20, this->getRect().y + this->getRect().h - temp.h / 2 - 150, temp.w, temp.h };
			enemiesStandardProjectile.push_back(projRect);
			projRect = { bossRect.x - temp.w + bossRect.w / 2, this->getRect().y + this->getRect().h - temp.h / 2, temp.w, temp.h };
			enemiesStandardProjectile.push_back(projRect);
			projRect = { bossRect.x - temp.w + bossRect.w / 4 - 10, this->getRect().y + this->getRect().h - temp.h / 2 - 75, temp.w, temp.h };
			enemiesStandardProjectile.push_back(projRect);
			projRect = { bossRect.x - temp.w + bossRect.w * 3 / 4 + 10, this->getRect().y + this->getRect().h - temp.h / 2 - 75, temp.w, temp.h };
			enemiesStandardProjectile.push_back(projRect);
			lastStandardShot = curShot;
			tripleStandardHit++;
		}
		else {
			lastStandardShot = curShot;
			tripleStandardHit = 0;
		}
	} 
	
	if (curShot > lastOrbCircle + 4000) {
		orbCircle.clear();
		orbDeleted.clear();
		int orbStartX = objRect.x + objRect.w / 2;
		int orbStartY = objRect.y + objRect.h;
		for (int i = 0; i < 24; i++) {
			orbDeleted.push_back(false);
			orbCircle.push_back({orbStartX, orbStartY, orb.getRect().w, orb.getRect().h});
		}
		std::cout << orbCircle.size() << std::endl;
		lastOrbCircle = curShot;
	}
}

//void AirCraftBoss::interactWithPlayer(Player& player) {
//	player.hitEnemy(*this);
//	player.enemyContact(*this);
//	player.hitByAirCraftBoss(*this);
//}

void AirCraftBoss::moveOrbCircle() {
	for (int i = 0; i < orbCircle.size(); i++) {
		orbCircle[i].x += cos(15 * (i % 24)) * BOSS_ORB_SPEED;
		orbCircle[i].y += sin(15 * (i % 24)) * BOSS_ORB_SPEED;
	}
}

void AirCraftBoss::showProjectiles(SDL_Renderer* screen) {
	showStandardProjectiles(screen);
	showOrbCircle(screen);
	standardProjectileMove();
	moveOrbCircle();
}

void AirCraftBoss::showOrbCircle(SDL_Renderer* screen) {
	for (int i = 0; i < orbCircle.size(); i++) {
		if (orbDeleted[i]) {
			continue;
		}
		orb.setRect(orbCircle[i]);
		orb.render(screen, NULL);
	}
}

std::vector<SDL_Rect> AirCraftBoss::getHitBoxes() {
	std::vector<SDL_Rect> result;
	SDL_Rect temp = { objRect.x, objRect.y + 103, 45, 130 };
	result.push_back(temp);
	temp = { objRect.x + objRect.w - 45, objRect.y + 103, 45, 130 };
	result.push_back(temp);
	temp = { objRect.x + 45, objRect.y, objRect.w - 90, objRect.h };
	result.push_back(temp);
	return result;
}