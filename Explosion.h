#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"

class Explosion : public BaseObject {
public:
	~Explosion();
	bool loadImage(std::string path, SDL_Renderer* des);
	void show(SDL_Renderer* des, int i);
private:
	std::vector<SDL_Rect> clip;
	int frameWidth;
	int frameHeight;
};