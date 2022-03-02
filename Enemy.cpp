#include "Enemy.h"

Enemy::Enemy() {
    xPos = 0;
    yPos = 0;
    currentFrame = 0;
    frameHeight = 0;
    frameWidth = 0;
    horizontalDirection = MOVE_RIGHT;
    verticalDirection = MOVE_DOWN;
    changeDelay = 0;
    alive = true;
}

Enemy::~Enemy() {

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

void Enemy::newPos() {

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

void Enemy::show(SDL_Renderer* des) {

    SDL_Rect renderQuad = { xPos, yPos, frameWidth, frameHeight };

    SDL_Rect* renderClip = &frameClip[currentFrame];

    SDL_RenderCopy(des, objTexture, renderClip, &renderQuad);

    currentFrame++;
    currentFrame %= ENEMY_ANIMATION_COUNT;

    changeDelay++;
    changeDelay %= 5;
    if (changeDelay == 0) {
        newPos();
    }

    //std::cout <<currentFrame <<std::endl;
}

SDL_Rect Enemy::getHitBox() {
    SDL_Rect result = { xPos, yPos, frameWidth, frameHeight };
    return result;
}


