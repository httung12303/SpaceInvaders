#include "Enemy.h"

Enemy::Enemy() {
    xPos = 0;
    yPos = 0;
    currentFrame = 0;
    frameHeight = 0;
    frameWidth = 0;
    horizontalDirection = MOVE_RIGHT;
    verticalDirection = MOVE_DOWN;
    lastMove = SDL_GetTicks();
    lastStandardShot = SDL_GetTicks();
    alive = true;
    hp = 3;
}

Enemy::~Enemy() {
    BaseObject::Free();
    standardProjectile.Free();
}

bool Enemy::loadImage(std::string path, SDL_Renderer* screen) {

    bool check = BaseObject::loadImage(path, screen);

    if (check) {
        //std::cout << objRect.w << ' ' << objRect.h << std::endl;
        frameWidth = objRect.w / ENEMY_ANIMATION_COUNT;
        frameHeight = objRect.h;
    }

    return check;

}

void Enemy::setClip() {
    if (frameHeight > 0 && frameWidth > 0) {
        for (int i = 0; i < ENEMY_ANIMATION_COUNT; i++) {
            frameClip[i].w = frameWidth;
            frameClip[i].h = frameHeight;
            frameClip[i].x = i * frameWidth;
            frameClip[i].y = 0;
        }
        minXPos = 0;
        maxXPos = WINDOW_WIDTH - frameWidth;

        minYPos = 0;
        maxYPos = WINDOW_HEIGHT - 3 * frameHeight;

    }
}

void Enemy::randomNewPos() {

    unsigned int curMove = SDL_GetTicks();
    if (curMove < lastMove + 1000) {
        return;
    }

    lastMove = curMove;

    horizontalDirection = rand() % 3;
    verticalDirection = rand() % 3;

    if (xPos == maxXPos) {
        horizontalDirection = MOVE_LEFT;
        //yPos = yPos + ENEMY_VERTICAL_SPEED;
        //if(yPos > maxYPos) yPos = maxYPos;
    }
    else if (xPos == minXPos) {
        horizontalDirection = MOVE_RIGHT;
        //yPos = yPos + ENEMY_VERTICAL_SPEED;
        //if(yPos > maxYPos) yPos = maxYPos;
    }

    if (horizontalDirection == MOVE_LEFT) {
        xPos -= ENEMY_HORIZONTAL_SPEED;
        if (xPos < minXPos) xPos = minXPos;
    }
    else if (horizontalDirection == MOVE_RIGHT) {
        xPos += ENEMY_HORIZONTAL_SPEED;
        if (xPos > maxXPos) xPos = maxXPos;
    }

    if (verticalDirection == MOVE_DOWN) {
        yPos += ENEMY_VERTICAL_SPEED;
        if (yPos > maxYPos) yPos = maxYPos;
    }
    else if (verticalDirection == MOVE_UP) {
        yPos -= ENEMY_VERTICAL_SPEED;
        if (yPos < minYPos) yPos = minYPos;
    }
}

void Enemy::show(SDL_Renderer*& des) {

    //std::cout << getObjectTexture() << std::endl;

    unsigned int curFrameTick = SDL_GetTicks();
    if (curFrameTick >= lastFrameTick + FRAME_DELAY) {
        currentFrame++;
        currentFrame %= ENEMY_ANIMATION_COUNT;
        lastFrameTick = curFrameTick;
    }

    SDL_Rect renderQuad = { xPos, yPos, frameWidth, frameHeight };

    SDL_Rect* renderClip = &frameClip[currentFrame];

    if (SDL_RenderCopy(des, objTexture, renderClip, &renderQuad) < 0) {
        std::cout << SDL_GetError() << '\n';
        exit(1);
    }

    //std::cout <<currentFrame <<std::endl;
}


SDL_Rect Enemy::getHitBox() {
    SDL_Rect result = { xPos, yPos, frameWidth, frameHeight };
    return result;
}

void Enemy::shoot() {
    unsigned int curShot = SDL_GetTicks();
    if (curShot < lastStandardShot + 1000) {
        return;
    }
    SDL_Rect temp = standardProjectile.getRect();
    SDL_Rect projRect = { xPos + frameWidth / 2 - temp.w / 2, yPos - temp.h / 2, temp.w, temp.h };
    enemiesStandardProjectile.push_back(projRect);
    lastStandardShot = curShot;
}

void Enemy::loadProjectile(std::string path, SDL_Renderer* screen) {
    if (!standardProjectile.loadImage(path, screen)) {
        std::cout << SDL_GetError() << '\n';
    }
}

void Enemy::showStandardProjectiles(SDL_Renderer* des) {
    for (int i = 0; i < enemiesStandardProjectile.size(); i++) {
        standardProjectile.setRect(enemiesStandardProjectile[i]);
        standardProjectile.render(des, NULL);
    }

    standardProjectileMove();
}

void Enemy::standardProjectileMove() {
    for (int i = 0; i < enemiesStandardProjectile.size(); i++) {
        enemiesStandardProjectile[i].y += ENEMY_STANDARD_PROJ_SPEED;
        if (enemiesStandardProjectile[i].y >= WINDOW_HEIGHT) {
            enemiesStandardProjectile.erase(enemiesStandardProjectile.begin() + (i--));
        }
    }
}
