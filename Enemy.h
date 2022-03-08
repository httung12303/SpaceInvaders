#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"
#include <cstdlib>

class Enemy : public BaseObject {
public:
    Enemy();
    ~Enemy();
    bool loadImage(std::string path, SDL_Renderer* screen) override;
    SDL_Rect getHitBox() override;
    void setClip();
    void show(SDL_Renderer*& des);
    void randomNewPos();
    void setPos(const int& x, const int& y) { xPos = x; yPos = y; }
    float getXPos() { return xPos; }
    float getYPos() { return yPos; }
    void changeXPos(float amount) { xPos += amount; }
    void changeYPos(float amount) { yPos += amount; }
    void hitByProjectile(std::vector<SDL_Rect>& projectiles);
    bool isAlive() { return alive; }
    void dead() { alive = false; }
    void getHit(const int& damage) { hp -= damage; }
    void setHP(const int& hp) { this->hp = hp; }
    int getHP() { return hp; }
    void loadProjectile(std::string path, SDL_Renderer* screen);
    void shoot();
    void projectileMove();
    void showProjectiles(SDL_Renderer* des);
    void eraseProjectile(int i) { projectiles.erase(projectiles.begin() + i); }
    std::vector<SDL_Rect> getProjectiles() { return projectiles; };
private:

    int hp;
    bool alive;

    float xPos;
    float yPos;

    int frameWidth;
    int frameHeight;

    int currentFrame;

    int maxYPos;
    int minYPos;
    int maxXPos;
    int minXPos;

    int horizontalDirection;
    int verticalDirection;

    SDL_Rect frameClip[ENEMY_ANIMATION_COUNT];

    unsigned int lastMove = 0;
    unsigned int lastShot = 0;
    unsigned int lastFrameTick = 0;

    BaseObject projectileObject;
    std::vector < SDL_Rect > projectiles;

    unsigned int frameChangeCooldown = 100;

};
