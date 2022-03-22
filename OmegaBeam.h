#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"

class OmegaBeam : public BaseObject {
public:
	~OmegaBeam();
	bool loadImage(const std::string& path, SDL_Renderer* screen);
	void show(SDL_Renderer* screen, int i);
	int getFrameWidth() { return frameWidth; }
	int getFrameHeight() { return frameHeight; }
private:
	std::vector<SDL_Rect> clip;
	int frameWidth;
	int frameHeight;
};