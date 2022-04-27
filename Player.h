#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"
#include "Enemy.h"
#include "AirCraftBoss.h"
#include <vector>

class Player : public BaseObject {
public:
    Player(SDL_Renderer* screen);
    ~Player();

    bool loadImage(std::string path, SDL_Renderer* screen) override;
    SDL_Rect getHitBox() override;
    void setClip();
    void show(SDL_Renderer* des);
    void handleInput(SDL_Event& e, SDL_Renderer* screen, SDL_Window* window);
    void resetPos();
    void shoot(SDL_Renderer* screen);
    void loadProjectile(std::string path, SDL_Renderer* screen);
    void projectileMove();
    bool isAlive() { return alive;}
    void hitEnemy(Enemy& enemy);
    void showProjectiles(SDL_Renderer* des);
    void enemyContact(Enemy& enemy);
    void dead() { alive = 0; }
    int getSpawnX() { return spawnXPos; }
    int getSpawnY() { return spawnYPos; }
    int getFrameWidth() { return frameWidth; }
    int getFrameHeight() { return frameHeight; }
    void hitByStandardProjectiles(Enemy& enemy);
    void hitByOrbCircle(AirCraftBoss& boss);
    void hitByHomingMissile(AirCraftBoss& boss);
    void hitByAirCraftBoss(AirCraftBoss& boss);
    bool getHit();
    void hitAirCraftBoss(AirCraftBoss& boss);
    void hitByOmegaBeam(AirCraftBoss& boss);
    void reset();
    float getXPos() { return xPos; }
    float getYPos() { return yPos; }
    void heal() { hp++; }
    int getHP() { return hp; }
    void increaseNumberOfProjectiles() { if(numberOfProjectiles < MAX_NUMBER_OF_PROJECTILES) numberOfProjectiles++; }
	void decreaseNumberOfProjectiles() { if(numberOfProjectiles > 1) numberOfProjectiles--; }
	int getNumberOfProjectiles() { return numberOfProjectiles; }
    void increaseAttackSpeed() { if (attackGap > MIN_ATTACK_GAP) attackGap -= 200; }
    void decreaseAttackSpeed() {if(attackGap < MAX_ATTACK_GAP) attackGap += 200; }
    unsigned int getAttackGap() { return attackGap; }
private:
    
    int hp;

    bool alive;

    int damage;

    unsigned int lastShot = 0;
    unsigned int lastHitByEnemy = 0;
    unsigned int lastFrameTick = 0;
    unsigned int attackGap;

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

    int horizontalMove = 0;
    int verticalMove = 0;

    int numberOfProjectiles;
	
    BaseObject projectile;
    BaseObject heart;

    std::vector < SDL_Rect > projectiles;

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
};
