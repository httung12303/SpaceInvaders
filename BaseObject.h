#pragma once

#include "BasicFunction.h"

class BaseObject {

public:
    BaseObject();
    ~BaseObject();
    void setRect(const int& x, const int& y) { objRect.x = x; objRect.y = y; }
    void setRect(const SDL_Rect other) { objRect = other; }
    void setRectSize(const int& w, const int& h) { objRect.w = w; objRect.h = h; }
    SDL_Rect getRect() const { return objRect; }
    SDL_Texture* getObjectTexture() const { return objTexture; }

    virtual bool loadImage(std::string path, SDL_Renderer* screen);
    void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    virtual SDL_Rect getHitBox();
    void Free();

protected:
    SDL_Texture* objTexture = NULL;
    SDL_Rect objRect;
};

