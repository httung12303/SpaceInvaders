#include "EnemyFormation.h"

EnemyFormation::EnemyFormation(const std::string path) {
	formationType = path;
	enemies.clear();
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cout << "File not opened: " + path << std::endl;
		exit(1);
	}
	int x;
	int y;
	enemiesAlive = 0;
	while (file >> x >> y) {
		Enemy newEnemy;
		newEnemy.setPos(x, y);
		enemies.push_back(newEnemy);
		posIndex[enemiesAlive] = enemiesAlive;
		xPosArr[enemiesAlive] = x;
		yPosArr[enemiesAlive++] = y;
		//std::cout << xPosArr[cnt - 1] << ' ' << yPosArr[cnt - 1] << std::endl;
	}
	file.close();
	lastMove = SDL_GetTicks();
}

EnemyFormation::~EnemyFormation() {
	enemies.clear();
}

void EnemyFormation::loadEnemies(const std::string imagePath, SDL_Renderer* screen) {
	for (Enemy& enemy : enemies) {
		if (!enemy.loadImage(imagePath, screen)) {
			std::cout << "EnemyFormation::loadEnemies" << std::endl;
		}
		else {
			enemy.setClip();
		}
	}

	/*for (Enemy enemy : enemies) {
		std::cout << enemy.getObjectTexture() << std::endl;
		std::cout << enemy.xPos << ' ' << enemy.yPos << ' ' << enemy.frameWidth << ' ' << enemy.frameHeight << std::endl;
	}*/

}

void EnemyFormation::loadProjectiles(const std::string path, SDL_Renderer* screen) {
	for (Enemy& enemy : enemies) {
		enemy.loadProjectile(path, screen);
	}
}

void EnemyFormation::show(SDL_Renderer* screen) {
	for (Enemy& enemy : enemies) {
		if (enemy.isAlive()) {
			enemy.show(screen);
		}
		enemy.showStandardProjectiles(screen);
	}
}

void EnemyFormation::interactWithPlayer(Player& player) {
	for (int i = 0; i < enemies.size(); i++) {

		if (player.isAlive() && enemies[i].isAlive()) {
			player.hitEnemy(enemies[i]);
			player.enemyContact(enemies[i]);
			player.hitByStandardProjectiles(enemies[i]);
			if (rand() % 50 == 1) {
				enemies[i].shoot();
			}
			if (!enemies[i].isAlive()) {
				enemiesAlive--;
			}
		}
	}
}

void EnemyFormation::moveFormation() {
	if (formationType == STACKED_FORMATION) {
		if (enemiesAlive <= 10) {
			for (Enemy& enemy : enemies) {
				enemy.randomNewPos();
			}
		}
		else {
			int horizontalMove = -60;
			if (moveState == 0) horizontalMove = 60;
			unsigned int curMoveTick = SDL_GetTicks();
			if (lastMove + 1000 < curMoveTick) {
				for (Enemy& enemy : enemies) {
					enemy.changeXPos(horizontalMove);
				}
				lastMove = curMoveTick;
				moveState++;
				moveState %= 2;
			}
		}
	}
	else if (formationType == WHEEL_FORMATION) {
		unsigned int curMoveTick = SDL_GetTicks();
		if (lastMove + 200 < curMoveTick) {
			for (int i = 0; i < 14; i++) {
				int tempX = (xPosArr[(posIndex[i] + 1) % 14] - xPosArr[posIndex[i]]) / 8;
				int tempY = (yPosArr[(posIndex[i] + 1) % 14] - yPosArr[posIndex[i]]) / 8;

				enemies[i].changeXPos(tempX);
				enemies[i].changeYPos(tempY);
				if (moveState == 8) {
					posIndex[i] = (posIndex[i] + 1) % 14;
				}
			}

			for (int i = 14; i < 22; i++) {
				int tempX = (xPosArr[(posIndex[i] - 1 - 14 + 8) % 8 + 14] - xPosArr[posIndex[i]]) / 8;
				int tempY = (yPosArr[(posIndex[i] - 1 - 14 + 8) % 8 + 14] - yPosArr[posIndex[i]]) / 8;

				enemies[i].changeXPos(tempX);
				enemies[i].changeYPos(tempY);
				if (moveState == 8) {
					posIndex[i] = (posIndex[i] - 1 - 14 + 8) % 8 + 14;
				}
			}
			lastMove = curMoveTick;
			moveState++;
			moveState %= 9;
		}
	}
}