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

void EnemyFormation::show(SDL_Renderer* screen) {
	for (Enemy &enemy : enemies) {
		enemy.show(screen);
	}
}

void EnemyFormation::interactWithPlayer(Player& player) {

}