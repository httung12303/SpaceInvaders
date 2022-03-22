#include "OmegaBeam.h"

OmegaBeam::~OmegaBeam() {

}

bool OmegaBeam::loadImage(const std::string& path, SDL_Renderer* screen) {

    SDL_Texture* tempTexture = NULL;
    SDL_Surface* imageSurface = NULL;
    imageSurface = IMG_Load(path.c_str());
    //std::cout << imageSurface << '\n';
    if (imageSurface != NULL) {
        SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format, 0, 0, 0));
        tempTexture = SDL_CreateTextureFromSurface(screen, imageSurface);
    }
    else errorLog(std::cout, "load omega beam", true);

    if (tempTexture != NULL) {
        objRect.w = imageSurface->w;
        objRect.h = imageSurface->h;
    }
    else errorLog(std::cout, "load omega beam", true);

    SDL_FreeSurface(imageSurface);
    imageSurface = NULL;

    objTexture = tempTexture;

    //std::cout << 1 << ' ' << objRect.w << ' ' << objRect.h << '\n';
	frameWidth = objRect.w;
	frameHeight = objRect.h / 12;
	for (int i = 0; i < 12; i++) {
		clip.push_back({ 0, i * frameHeight, frameWidth, frameHeight });
	}

    return true;
}

void OmegaBeam::show(SDL_Renderer* screen, int i) {
	render(screen, &clip[i]);
}