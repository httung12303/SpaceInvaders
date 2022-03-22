#include "Explosion.h"


bool Explosion::loadImage(std::string path, SDL_Renderer* des) {
	if (!BaseObject::loadImage(path.c_str(), des)) {
		errorLog(std::cout, "load explosion", false);
		return false;
	}
	for (int i = 0; i < 56; i++) {
		clip.push_back({ (i % 10) * 120, (int)(i / 10) * 120, objRect.w / 10, objRect.h / 6});
		//std::cout << (i % 10) * 120 << ' ' << (int)(i / 10) * 120 << ' ' << objRect.w / 10 << ' ' << objRect.h / 6 << std::endl;
	}
	frameWidth = objRect.w / 10;
	frameHeight = objRect.h / 6;
	return true;
}

Explosion::~Explosion() {
	Free();
}

void Explosion::show(SDL_Renderer* des,int i) {
	SDL_Rect tempRect = { objRect.x, objRect.y, frameWidth, frameHeight };
	SDL_RenderCopy(des, objTexture, &clip[i], &tempRect);
}