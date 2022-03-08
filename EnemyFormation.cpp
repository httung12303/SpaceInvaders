#include "EnemyFormation.h"
#include <fstream>
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
	while (file >> x >> y) {
		Enemy newEnemy;
		newEnemy.setPos(x, y);
		enemies.push_back(newEnemy);
	}
	file.close();
	lastMove = SDL_GetTicks();
}

EnemyFormation::~EnemyFormation() {

}

void EnemyFormation::loadEnemies(const std::string imagePath, SDL_Renderer* screen) {
	for (Enemy &enemy : enemies) {
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
	for (Enemy &enemy : enemies) {
		enemy.show(screen);
		enemy.showProjectiles(screen);
	}
}

void EnemyFormation::interactWithPlayer(Player& player) {
	for (int i = 0; i < enemies.size();) {
		if (!enemies[i].isAlive()) {
			enemies.erase(enemies.begin() + i);
			continue;
		}
		enemies[i].shoot();
		if (player.isAlive()) {
			player.hitEnemy(enemies[i]);
			player.enemyContact(enemies[i]);
			player.hitByEnemy(enemies[i]);
		}
		i++;
	}
}

void EnemyFormation::moveFormation() {
	if (formationType == STACKED_FORMATION) {
		if (enemies.size() <= 5) {
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
	/*for (Enemy& enemy : enemies) {
		enemy.randomNewPos();
	}*/
}