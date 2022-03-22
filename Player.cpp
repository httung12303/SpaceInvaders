#include "Player.h"

Player::Player(SDL_Renderer* screen) {

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
    loadImage("images/Characters/plane.png", screen);
    setClip();
    resetPos();
    loadProjectile("images/Projectile/rocket.png", screen);
}

Player::~Player() {
    projectile.Free();
    Mix_FreeChunk(fireSound);
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

    if (!(curFrameTick - lastHitByEnemy < 3000 && currentFrame % 2 == 1)) {
        SDL_Rect renderQuad = { xPos, yPos, frameWidth, frameHeight };

        SDL_Rect* clip = &frameClip[currentFrame];

        SDL_RenderCopy(des, objTexture, clip, &renderQuad);
    }

}

void Player::showProjectiles(SDL_Renderer* des) {
    for (int i = 0; i < projectiles.size(); i++) {
        projectile.setRect(projectiles[i]);
        projectile.render(des, NULL);
    }

    projectileMove();
}

void Player::handleInput(SDL_Event& e, SDL_Renderer* screen, SDL_Window* window) {

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

        if (keyboardState[SDL_SCANCODE_SPACE]) {
            unsigned int curShot = SDL_GetTicks();
            if (curShot - lastShot >= 200) {
                shoot(screen);
                if (fireSound != NULL) {
                    Mix_VolumeChunk(fireSound, 5);
                    Mix_PlayChannel(-1, fireSound, 0);
                }
                lastShot = curShot;
            }
        }
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN) {
        unsigned int curShot = SDL_GetTicks();
        if (curShot - lastShot >= 200) {
            shoot(screen);
            if (fireSound != NULL) {
                Mix_VolumeChunk(fireSound, 5);
                Mix_PlayChannel(-1, fireSound, 0);
            }
            lastShot = curShot;
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
    if (!projectile.loadImage(path, screen)) {
        std::cout << SDL_GetError() << '\n';
    }
}

void Player::shoot(SDL_Renderer* screen) {
    SDL_Rect temp = projectile.getRect();
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
    SDL_Rect result = { xPos + frameWidth / 3, yPos, frameWidth / 3, frameHeight };
    return result;
}

void Player::hitEnemy(Enemy& enemy) {
    SDL_Rect hitbox = enemy.getHitBox();

    for (int i = 0; i < projectiles.size(); i++) {
        SDL_Rect cur = projectiles[i];
        //if (hitbox.x >= cur.x + cur.w || hitbox.x + hitbox.w <= cur.x || hitbox.y >= cur.y + cur.h || hitbox.y + hitbox.h <= cur.y)
        if (!overlap(cur, hitbox))
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
    if (overlap(playerHitbox, enemyHitbox))
        getHit();
}

void Player::hitByStandardProjectiles(Enemy& enemy) {

    std::vector<SDL_Rect> enemyProjectiles = enemy.getProjectiles();
    SDL_Rect playerHitBox = this->getHitBox();
    //std::cout << enemyProjectiles.size() << '\n';
    for (int i = 0; i < enemyProjectiles.size();) {
        SDL_Rect cur = enemyProjectiles[i];
        if (!overlap(playerHitBox, cur)) {
            i++;
            continue;
        }
        if (getHit()) {
            enemy.eraseStandardProjectile(i);
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

void Player::loadFireSound(const std::string path) {
    fireSound = Mix_LoadWAV(path.c_str());
    if (fireSound == NULL) {
        std::cout << Mix_GetError() << std::endl;
    }
}

void Player::hitByOrbCircle(AirCraftBoss& boss) {
    std::vector<SDL_Rect> orbCircle = boss.getOrbCircle();
    std::vector<bool> orbState = boss.getOrbState();
    SDL_Rect playerHitBox = this->getHitBox();
    for (int i = 0; i < orbCircle.size();) {
        if (!overlap(orbCircle[i], playerHitBox)) {
            i++;
            continue;
        }
        if (!orbState[i] && getHit()) {
            boss.deleteOrb(i);
        }
        else {
            i++;
        }
    }
}

void Player::hitByHomingMissile(AirCraftBoss& boss) {
    std::vector<SDL_Rect> missileRect = boss.getHomingMissilesRect();
    std::vector<bool> missileState = boss.getHomingMissilesState();
    SDL_Rect playerHitBox = this->getHitBox();
    for (int i = 0; i < missileRect.size();) {
        if (!overlap(missileRect[i], playerHitBox)) {
            i++;
            continue;
        }
        if (!missileState[i] && getHit()) {
            boss.deleteHomingMissile(i);
        }
        else {
            i++;
        }
    }
}

void Player::hitByAirCraftBoss(AirCraftBoss& boss) {
    hitByStandardProjectiles(boss);
    hitByOrbCircle(boss);
    hitByHomingMissile(boss);
    hitByOmegaBeam(boss);
}

void Player::hitAirCraftBoss(AirCraftBoss& boss) {
    if (!boss.isAlive()) {
        return;
    }
    std::vector<SDL_Rect> hitboxes = boss.getHitBoxes();
    for (int i = 0; i < projectiles.size(); i++) {
        for (int j = 0; j < hitboxes.size(); j++) {
            if (overlap(projectiles[i], hitboxes[j]) && boss.isAlive()) {
                boss.getHit(damage);
                projectiles.erase(projectiles.begin() + (i--));
                break;
            }
        }
    }
}

void Player::hitByOmegaBeam(AirCraftBoss& boss) {
    std::vector<SDL_Rect> omegaBeamHitboxes = boss.getOmegaBeamRects();
    SDL_Rect playerHitbox = this->getHitBox();
    for (int i = 0; i < omegaBeamHitboxes.size(); i++) {
        omegaBeamHitboxes[i].x += 30;
        omegaBeamHitboxes[i].w = 70;
        if (overlap(omegaBeamHitboxes[i], playerHitbox)) {
            getHit();
        }
    }
}