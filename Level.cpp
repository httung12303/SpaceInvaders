#include "Level.h"

Level::Level(SDL_Renderer* screen) {
	extraHitPointPowerUp = new PowerUp();
	extraHitPointPowerUp->loadImage("images/Power Ups/extraHitPoint.png", screen);
	extraHitPointPowerUp->setRectSize(35, 35);

	extraShotPowerUp = new PowerUp();
	extraShotPowerUp->loadImage("images/Power Ups/extraProjectile.png", screen);
	extraShotPowerUp->setRectSize(35, 35);

	increaseAttackSpeedPowerUp = new PowerUp();
	increaseAttackSpeedPowerUp->loadImage("images/Power Ups/increaseAttackSpeed.png", screen);
	increaseAttackSpeedPowerUp->setRectSize(35, 35);

	lastPowerUp = SDL_GetTicks();
}

void Level::insertRandomPowerUp() {
	if (SDL_GetTicks() < lastPowerUp + 3000) {
		return;
	}
	int effect = rand() % 3;
	int x = rand() % (WINDOW_WIDTH - 35);
	SDL_Rect rect = { x, 0, 35, 35 };
	powerUps.push_back(PowerUpInfo(rect, effect));
	lastPowerUp = SDL_GetTicks();
}

void Level::movePowerUps() {
	for (int i = 0; i < powerUps.size(); i++) {
		powerUps[i].rect.y += POWER_UP_FALL_SPEED;
		if (powerUps[i].rect.y > WINDOW_HEIGHT) {
			powerUps.erase(powerUps.begin() + (i--));
		}
	}
}

void Level::renderPowerUps(SDL_Renderer* screen) {
	for(PowerUpInfo powerUp : powerUps) {
		if (powerUp.effect == EXTRA_HITPOINT_POWER_UP) {
			extraHitPointPowerUp->setRect(powerUp.rect);
			extraHitPointPowerUp->render(screen, NULL);
		}
		else if (powerUp.effect == EXTRA_SHOT_POWER_UP) {
			extraShotPowerUp->setRect(powerUp.rect);
			extraShotPowerUp->render(screen, NULL);
		}
		else if (powerUp.effect == INCREASE_ATTACK_SPEED_POWER_UP) {
			increaseAttackSpeedPowerUp->setRect(powerUp.rect);
			increaseAttackSpeedPowerUp->render(screen, NULL);
		}
	}
}

void Level::playerPowerUp(Player& player) {
	for(int i = 0; i < powerUps.size(); i++) {
		if (overlap(player.getHitBox(), powerUps[i].rect)) {
			if (powerUps[i].effect == EXTRA_HITPOINT_POWER_UP && player.getHP() < MAX_HP) {
				player.heal();
			}
			else if (powerUps[i].effect == EXTRA_SHOT_POWER_UP) {
				player.increaseNumberOfProjectiles();
			}
			else if (powerUps[i].effect == INCREASE_ATTACK_SPEED_POWER_UP) {
				player.increaseAttackSpeed();
			}
			powerUps.erase(powerUps.begin() + (i--));
		}
	}
}