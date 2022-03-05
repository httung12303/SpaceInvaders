#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"
#include "Enemy.h"

class Player : public BaseObject {
public:
    Player();
    ~Player();

    bool loadImage(std::string path, SDL_Renderer* screen) override;
    SDL_Rect getHitBox() override;
    void setClip();
    void show(SDL_Renderer* des);
    void handleInput(SDL_Event e, SDL_Renderer* screen);
    void resetPos();
    void shoot(SDL_Renderer* screen);
    void loadProjectile(std::string path, SDL_Renderer* screen);
    void projectileMove();
    bool isAlive() { return alive;}
    void hitEnemy(Enemy& enemy);
    void showProjectiles(SDL_Renderer* des);
    void enemyContact(Enemy& enemy);
    void dead() { alive = 0; }

private:
    
    int lives;

    bool alive;

    int damage;

    unsigned int lastShot = 0;
    unsigned int lastHitByEnemy = 0;

    float xPos;
    float yPos;

    int frameWidth;
    int frameHeight;

    SDL_Rect frameClip[PLAYER_ANIMATION_COUNT];

    //Input input;

    int currentFrame;

    int spawnXPos;
    int spawnYPos;

    int maxYPos;
    int minYPos;
    int maxXPos;
    int minXPos;

    BaseObject projectileObject;

    std::vector < SDL_Rect > projectiles;

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
};
