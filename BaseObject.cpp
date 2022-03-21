#include "BaseObject.h"
#include "BasicFunction.h"

BaseObject::BaseObject() {
    objRect = { 0, 0, 0, 0 };
    objTexture = NULL;
}

BaseObject::~BaseObject() {
    Free();
}

bool BaseObject::loadImage(std::string path, SDL_Renderer* screen) {

    SDL_Texture* tempTexture = NULL;
    SDL_Surface* imageSurface = NULL;
    imageSurface = IMG_Load(path.c_str());
    //std::cout << imageSurface << '\n';
    if (imageSurface != NULL) {
        SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format, COLOR_KEY_RED, COLOR_KEY_GREEN, COLOR_KEY_BLUE));
        tempTexture = SDL_CreateTextureFromSurface(screen, imageSurface);
    }
    else std::cout << "Load failed\n";

    if (tempTexture != NULL) {
        objRect.w = imageSurface->w;
        objRect.h = imageSurface->h;
    }
    else std::cout << "Load failed\n" << SDL_GetError();

    SDL_FreeSurface(imageSurface);
    imageSurface = NULL;

    objTexture = tempTexture;

    //std::cout << 1 << ' ' << objRect.w << ' ' << objRect.h << '\n';

    return objTexture != NULL;

}

void BaseObject::render(SDL_Renderer* des, const SDL_Rect* clip) {

    //SDL_Rect tempRect = {objRect.x, objRect.y, objRect.w, objRect.h};
    //std::cout << des << std::endl;
    SDL_RenderCopy(des, objTexture, clip, &objRect);

}

void BaseObject::Free() {

    if (objTexture != NULL) {
        SDL_DestroyTexture(objTexture);
        objTexture = NULL;
        objRect.x = 0;
        objRect.y = 0;
    }
}

SDL_Rect BaseObject::getHitBox() {
    return objRect;
}

void BaseObject::render(SDL_Renderer* des, double angle, const SDL_Point* center, SDL_RendererFlip flip, SDL_Rect* clip ) {
    //SDL_Point point = { objRect.x / 2, objRect.y / 2 };
    SDL_RenderCopyEx(des, objTexture, clip, &objRect, angle, center, flip);
}
