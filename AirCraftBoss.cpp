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
	homingMissile.loadImage("images/Projectile/Super_Buddy.png", screen);
	enemiesStandardProjectile.clear();
	orbCircle.clear();
	orbDeleted.clear();
	homingMissilesRect.clear();
	homingMissilesAngle.clear();
	setRect(WINDOW_WIDTH / 2 - this->getRect().w / 2, 0);
	targetCenter = WINDOW_WIDTH / 2 - this->getRect().w / 2;
	alive = 1;
	hp = MAX_BOSS_HP;
	lastOrbCircle = 0;
	lastHomingMissiles = 0;
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
		SDL_Rect temp = standardProjectile.getRect();
		SDL_Rect bossRect = this->getRect();
		SDL_Rect projRect;
		projRect = { bossRect.x + 20, bossRect.y + bossRect.h - temp.h / 2 - 150, temp.w, temp.h };
		enemiesStandardProjectile.push_back(projRect);
		projRect = { bossRect.x + bossRect.w - temp.w - 20, bossRect.y + bossRect.h - temp.h / 2 - 150, temp.w, temp.h };
		enemiesStandardProjectile.push_back(projRect);
		projRect = { bossRect.x - temp.w + bossRect.w / 2, bossRect.y + bossRect.h - temp.h / 2, temp.w, temp.h };
		enemiesStandardProjectile.push_back(projRect);
		projRect = { bossRect.x - temp.w + bossRect.w / 4 - 10, bossRect.y + bossRect.h - temp.h / 2 - 75, temp.w, temp.h };
		enemiesStandardProjectile.push_back(projRect);
		projRect = { bossRect.x - temp.w + bossRect.w * 3 / 4 + 10, bossRect.y + bossRect.h - temp.h / 2 - 75, temp.w, temp.h };
		enemiesStandardProjectile.push_back(projRect);
		lastStandardShot = curShot;
	}
	
	if (curShot > lastOrbCircle + 3000) {
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

	if (curShot > lastHomingMissiles + 5000) {
		homingMissilesRect.clear();
		homingMissilesAngle.clear();
		homingMissilesDeleted.clear();
		SDL_Rect temp = homingMissile.getRect();
		SDL_Rect bossRect = this->getRect();
		SDL_Rect projRect;
		projRect = { bossRect.x + bossRect.w / 2 - temp.w / 2, bossRect.y + bossRect.h, temp.w, temp.h };
		homingMissilesRect.push_back(projRect);
		homingMissilesAngle.push_back(40);
		homingMissilesDeleted.push_back(false);
		projRect = { bossRect.x + bossRect.w / 3 - temp.w / 2, 100, temp.w, temp.h };
		homingMissilesRect.push_back(projRect);
		homingMissilesAngle.push_back(180);
		homingMissilesDeleted.push_back(false);
		projRect = { bossRect.x + bossRect.w * 2 / 3 - temp.w / 2, 100, temp.w, temp.h };
		homingMissilesRect.push_back(projRect);
		homingMissilesAngle.push_back(180);
		homingMissilesDeleted.push_back(false);
		lastHomingMissiles = curShot;
	}
}

void AirCraftBoss::moveOrbCircle() {
	for (int i = 0; i < orbCircle.size(); i++) {
		orbCircle[i].x += cos(M_PI * 15 * (i % 24) / 180) * BOSS_ORB_SPEED;
		orbCircle[i].y += sin(M_PI * 15 * (i % 24) / 180) * BOSS_ORB_SPEED;
	}
}

void AirCraftBoss::showProjectiles(SDL_Renderer* screen, const SDL_Rect& playerHitbox) {
	showStandardProjectiles(screen);
	showOrbCircle(screen);
	showHomingMissiles(screen);
	standardProjectileMove();
	moveOrbCircle();
	moveHomingMissiles(playerHitbox);
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

void AirCraftBoss::showHomingMissiles(SDL_Renderer* screen) {
	for (int i = 0; i < homingMissilesRect.size(); i++) {
		if (homingMissilesDeleted[i]) {
			continue;
		}
		SDL_Point p = { homingMissilesRect[i].x + homingMissilesRect[i].w / 2, homingMissilesRect[i].y + homingMissilesRect[i].h / 2 };
		homingMissile.setRect(homingMissilesRect[i]);
		homingMissile.render(screen, homingMissilesAngle[i], NULL, SDL_FLIP_NONE, NULL);
		//homingMissile.render(screen, NULL);
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

void AirCraftBoss::moveHomingMissiles(const SDL_Rect& playerHitbox) {
	for (int i = 0; i < homingMissilesRect.size(); i++) {
		if (homingMissilesDeleted[i]) {
			continue;
		}
		double omega = 10;
		double x = playerHitbox.x + playerHitbox.w / 2 - homingMissilesRect[i].x - homingMissilesRect[i].w / 2;
		double y = playerHitbox.y + playerHitbox.h / 2 - homingMissilesRect[i].y - homingMissilesRect[i].h / 2;
		double vecX = x / sqrt(x * x + y * y);
		double vecY = y / sqrt(x * x + y * y);
		homingMissilesRect[i].x += vecX * BOSS_HOMING_MISSILE_SPEED;
		homingMissilesRect[i].y += vecY * BOSS_HOMING_MISSILE_SPEED;
		double angle;
		if(x > 0) angle = 180 - acos(vecY) / M_PI * 180;
		else angle = acos(vecY) / M_PI * 180 + 180;
		if (homingMissilesAngle[i] - angle > 10) {
			homingMissilesAngle[i] -= omega;
		}
		else if (angle - homingMissilesAngle[i] > 10) {
			homingMissilesAngle[i] += omega;
		}
	} 
}