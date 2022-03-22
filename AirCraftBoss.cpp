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
	explosion.loadImage("images/Effects/explosion2.png", screen);
	omegaBeam.loadImage("images/Projectile/omegaBeam3.png", screen);
	enemiesStandardProjectile.clear();
	orbCircle.clear();
	orbDeleted.clear();
	homingMissilesRect.clear();
	homingMissilesAngle.clear();
	setRect(WINDOW_WIDTH / 2 - this->getRect().w / 2, - 50);
	targetCenter = WINDOW_WIDTH / 2 - this->getRect().w / 2;
	alive = 1;
	hp = MAX_BOSS_HP;
	lastOrbCircle = 0;
	lastHomingMissiles = 0;
	lastOmegaBeam = 0;
	omegaBeamFrame = 0;
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

	SDL_Rect bossRect = this->getRect();
	SDL_Rect projRect;

	if (curShot > lastOmegaBeam + 3000) {
		omegaBeams.clear();
	}

	if (curShot > lastHomingMissiles + 5000) {
		for (int i = 0; i < homingMissilesDeleted.size(); i++) {
			homingMissilesDeleted[i] = true;
		}
	}

	if (curShot > lastStandardShot + 1000) {
		SDL_Rect temp = standardProjectile.getRect();
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
	
	if (curShot > lastOrbCircle + 5000) {
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

	if (curShot > lastHomingMissiles + 10000) {
		homingMissilesRect.clear();
		homingMissilesAngle.clear();
		homingMissilesDeleted.clear();
		homingMissileExplosionState.clear();
		SDL_Rect temp = homingMissile.getRect();
		projRect = { bossRect.x + bossRect.w / 2 - temp.w / 2, bossRect.y + bossRect.h, temp.w, temp.h };
		homingMissilesRect.push_back(projRect);
		homingMissilesAngle.push_back(180);
		homingMissilesDeleted.push_back(false);
		homingMissileExplosionState.push_back(0);
		projRect = { bossRect.x, 100, temp.w, temp.h };
		homingMissilesRect.push_back(projRect);
		homingMissilesAngle.push_back(180);
		homingMissilesDeleted.push_back(false);
		homingMissileExplosionState.push_back(0);
		projRect = { bossRect.x + bossRect.w - temp.w, 100, temp.w, temp.h };
		homingMissilesRect.push_back(projRect);
		homingMissilesAngle.push_back(180);
		homingMissilesDeleted.push_back(false);
		homingMissileExplosionState.push_back(0);
		lastHomingMissiles = curShot;
	}

	if (curShot > lastOmegaBeam + 5000) {
		SDL_Rect temp = omegaBeam.getRect();
		projRect = { bossRect.x - 30, bossRect.y + bossRect.h - 170, omegaBeam.getFrameWidth(), omegaBeam.getFrameHeight() };
		omegaBeams.push_back(projRect);
		projRect = { bossRect.x + bossRect.w + 30, bossRect.y + bossRect.h - 170, omegaBeam.getFrameWidth(), omegaBeam.getFrameHeight() };
		omegaBeams.push_back(projRect);
		lastOmegaBeam = curShot;
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
	showExplosion(screen);
	showOmegaBeam(screen);
	standardProjectileMove();
	moveOrbCircle();
	moveHomingMissiles(playerHitbox);
	moveOmegaBeam();
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
		if (abs(x) < 10 && abs(y) < 10) deleteHomingMissile(i);
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

void AirCraftBoss::showExplosion(SDL_Renderer* screen) {
	for (int i = 0; i < homingMissilesRect.size(); i++) {
		if (!homingMissilesDeleted[i]) {
			continue;
		}
		if (homingMissileExplosionState[i] < 56) {
			explosion.setRect(homingMissilesRect[i].x, homingMissilesRect[i].y);
			explosion.show(screen, homingMissileExplosionState[i]++);
		}
	}
}

void AirCraftBoss::showOmegaBeam(SDL_Renderer* screen) {
	for (int i = 0; i < omegaBeams.size(); i++) {
		omegaBeam.setRect(omegaBeams[i]);
		omegaBeam.show(screen, omegaBeamFrame % 12);
	}
	omegaBeamFrame = (omegaBeamFrame + 1) % 12;
}

void AirCraftBoss::moveOmegaBeam() {
	if (omegaBeams.size() < 2) {
		return;
	}
	SDL_Rect bossRect = this->getRect();
	SDL_Rect projRect = { bossRect.x - 40, bossRect.y + bossRect.h - 180, omegaBeam.getFrameWidth(), omegaBeam.getFrameHeight() };
	omegaBeams[0] = projRect;
	projRect = { bossRect.x + bossRect.w - omegaBeam.getFrameWidth() + 45, bossRect.y + bossRect.h - 180, omegaBeam.getFrameWidth(), omegaBeam.getFrameHeight()};
	omegaBeams[1] = projRect;
}