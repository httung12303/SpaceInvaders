#include "Player.h"

Player::Player() {

    lives = 3;
    currentFrame = PLAYER_ANIMATION_COUNT / 2 - 1;
    xPos = 0;
    yPos = 0;
    frameWidth = 0;
    frameHeight = 0;
    alive = true;
    damage = 1;
    lastShot = SDL_GetTicks();
    lastFrameTick = SDL_GetTicks();
}

Player::~Player() {

}

bool Player::loadImage(std::string path, SDL_Renderer* screen) {

    bool check = BaseObject::loadImage(path, screen);

    if (check) {
        frameWidth = objRect.w / PLAYER_ANIMATION_COUNT;
        frameHeight = objRect.h;
    }

    return check;

}

void Player::setClip() {

    if (frameWidth > 0 && frameHeight > 0) {
        for (int i = 0; i < PLAYER_ANIMATION_COUNT; i++) {

            frameClip[i].w = frameWidth;
            frameClip[i].h = frameHeight;

            frameClip[i].x = frameWidth * i;
            frameClip[i].y = 0;

        }

        spawnXPos = WINDOW_WIDTH / 2 - frameWidth / 2;
        spawnYPos = WINDOW_HEIGHT / 10 * 9 - frameHeight / 2;

        minXPos = 20;
        maxXPos = WINDOW_WIDTH - frameWidth - 20;

        minYPos = 20;
        maxYPos = WINDOW_HEIGHT - frameHeight * 2 / 3 - 20;
    }

}

void Player::show(SDL_Renderer* des) {

    unsigned int curFrameTick = SDL_GetTicks();
    if (curFrameTick >= lastFrameTick + FRAME_DELAY) {
        currentFrame++;
        currentFrame %= PLAYER_ANIMATION_COUNT;
        lastFrameTick = curFrameTick;
    }
    
    SDL_Rect renderQuad = { xPos, yPos, frameWidth, frameHeight };

    SDL_Rect* clip = &frameClip[currentFrame];

    SDL_RenderCopy(des, objTexture, clip, &renderQuad);

}

void Player::showProjectiles(SDL_Renderer* des) {
    for (int i = 0; i < projectiles.size(); i++) {
        projectileObject.setRect(projectiles[i]);
        projectileObject.render(des, NULL);
    }

    projectileMove();
}

void Player::handleInput(SDL_Event e, SDL_Renderer* screen, SDL_Window* window) {

    if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
        if (keyboardState[SDL_SCANCODE_UP] && !keyboardState[SDL_SCANCODE_DOWN]) {
            yPos -= PLAYER_VERTICAL_SPEED;
            if (yPos < minYPos) yPos = minYPos;
            verticalMove = MOVE_UP;
            SDL_WarpMouseInWindow(window, xPos, yPos);
        }
        else if (!keyboardState[SDL_SCANCODE_UP] && keyboardState[SDL_SCANCODE_DOWN]) {
            yPos += PLAYER_VERTICAL_SPEED;
            if (yPos > maxYPos) yPos = maxYPos;
            verticalMove = MOVE_DOWN;
            SDL_WarpMouseInWindow(window, xPos, yPos);
        }
        else {
            verticalMove = IDLE;
        }
        
        if (keyboardState[SDL_SCANCODE_LEFT] && !keyboardState[SDL_SCANCODE_RIGHT]) {
            xPos -= PLAYER_HORIZONTAL_SPEED;
            if (xPos < minXPos) xPos = minXPos;
            horizontalMove = MOVE_LEFT;
            SDL_WarpMouseInWindow(window, xPos, yPos);
        }
        else if (!keyboardState[SDL_SCANCODE_LEFT] && keyboardState[SDL_SCANCODE_RIGHT]) {
            xPos += PLAYER_HORIZONTAL_SPEED;
            if (xPos > maxXPos) xPos = maxXPos;
            horizontalMove = MOVE_RIGHT;
            SDL_WarpMouseInWindow(window, xPos, yPos);
        }

        if (keyboardState[SDL_SCANCODE_SPACE] || (e.type == SDL_MOUSEBUTTONDOWN)) {
            if (e.type == SDL_MOUSEBUTTONDOWN) std::cout << "mousebuttondown" << std::endl;
            unsigned int curShot = SDL_GetTicks();
            if (curShot - lastShot >= 300) {
                shoot(screen);
                lastShot = curShot;
            }
        }  
    }
    else if (e.type == SDL_MOUSEMOTION) {
        xPos = e.motion.x;
        yPos = e.motion.y;

        if (yPos < minYPos) yPos = minYPos;
        if (yPos > maxYPos) yPos = maxYPos;
        if (xPos < minXPos) xPos = minXPos;
        if (xPos > maxXPos) xPos = maxXPos;

    }
}

void Player::resetPos() {
    xPos = spawnXPos;
    yPos = spawnYPos;
}

void Player::loadProjectile(std::string path, SDL_Renderer* screen) {
    if (!projectileObject.loadImage(path, screen)) {
        std::cout << SDL_GetError() << '\n';
    }
}

void Player::shoot(SDL_Renderer* screen) {
    SDL_Rect temp = projectileObject.getRect();
    SDL_Rect renderquad = { xPos + frameWidth / 2 - temp.w / 2, yPos - temp.h / 2, temp.w, temp.h };
    projectiles.push_back(renderquad);
}

void Player::projectileMove() {
    for (int i = 0; i < projectiles.size(); i++) {
        projectiles[i].y -= PLAYER_PROJ_SPEED;
        if (projectiles[i].y <= -projectiles[i].h) {
            projectiles.erase(projectiles.begin() + (i--));
        }
    }
}

SDL_Rect Player::getHitBox() {
    SDL_Rect result = { xPos, yPos, frameWidth, frameHeight };
    return result;
}

void Player::hitEnemy(Enemy& enemy) {
    SDL_Rect hitbox = enemy.getHitBox();

    for (int i = 0; i < projectiles.size(); i++) {
        SDL_Rect cur = projectiles[i];
        if (hitbox.x >= cur.x + cur.w || hitbox.x + hitbox.w <= cur.x || hitbox.y >= cur.y + cur.h || hitbox.y + hitbox.h <= cur.y)
            continue;
        if (!enemy.isAlive()) 
            continue;
        enemy.getHit(damage);
        projectiles.erase(projectiles.begin() + (i--));
        if(enemy.getHP() <= 0)
            enemy.dead();
    }
}

void Player::enemyContact(Enemy& enemy) {
    SDL_Rect playerHitbox = this->getHitBox();
    SDL_Rect enemyHitbox = enemy.getHitBox();
    //std::cout << playerHitbox.x << ' ' << playerHitbox.y << ' ' << playerHitbox.w << ' ' << playerHitbox.h << '\n';
    //std::cout << enemyHitbox.x << ' ' << enemyHitbox.y << ' ' << enemyHitbox.w << ' ' << enemyHitbox.h << '\n';
    if (playerHitbox.x >= enemyHitbox.x + enemyHitbox.w || playerHitbox.x + playerHitbox.w <= enemyHitbox.x || playerHitbox.y + playerHitbox.h <= enemyHitbox.y || playerHitbox.y >= enemyHitbox.y + enemyHitbox.h)
        return;
    getHit();
}

void Player::hitByEnemy(Enemy& enemy) {

    std::vector<SDL_Rect> enemyProjectiles = enemy.getProjectiles();
    SDL_Rect playerHitBox = this->getHitBox();
    //std::cout << enemyProjectiles.size() << '\n';
    for (int i = 0; i < enemyProjectiles.size();) {
        SDL_Rect cur = enemyProjectiles[i];
        if (playerHitBox.x > cur.x + cur.w || playerHitBox.x + playerHitBox.w < cur.x || playerHitBox.y > cur.y + cur.h || playerHitBox.y + playerHitBox.h < cur.y) {
            i++;
            continue;
        }
        if (getHit()) {
            enemy.eraseProjectile(i);
        }
        else {
            i++;
        }
    }
}

bool Player::getHit() {
    unsigned int cur = SDL_GetTicks();
    if (cur - lastHitByEnemy < 3000)
        return false;
    lastHitByEnemy = cur;
    lives--;
    if (lives <= 0) dead();
    return true;
}

