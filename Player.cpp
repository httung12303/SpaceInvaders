#include "Player.h"

Player::Player(SDL_Renderer* screen) {

    hp = 5;
    currentFrame = PLAYER_ANIMATION_COUNT / 2 - 1;
    xPos = 0;
    yPos = 0;
    frameWidth = 0;
    frameHeight = 0;
    alive = true;
    damage = 1;
    lastShot = 0;
    lastFrameTick = 0;
    loadImage("images/Characters/plane.png", screen);
    setClip();
    resetPos();
    loadProjectile("images/Projectile/rocket.png", screen);
    heart.loadImage("images/Characters/heart.png", screen);
    numberOfProjectiles = 1;
    attackGap = MAX_ATTACK_GAP;
}

Player::~Player() {
    projectile.Free();
    Free();
}

void Player::reset() {
    setRect(getSpawnX(), getSpawnY());
    hp = 5;
    alive = true;
    lastShot = SDL_GetTicks();
    lastFrameTick = SDL_GetTicks();
	projectiles.clear();
    resetPos();
    numberOfProjectiles = 1;
    attackGap = MAX_ATTACK_GAP;
    lastShot = 0;
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

    for (int i = 0; i < hp; i++) {
		heart.setRect(30 + i * (heart.getRect().w + 5), WINDOW_HEIGHT - heart.getRect().h - 10);
        heart.render(des, NULL);
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
            if (curShot - lastShot >= attackGap) {
                shoot(screen);
                lastShot = curShot;
            }
        }
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN) {
        unsigned int curShot = SDL_GetTicks();
        if (curShot - lastShot >= attackGap) {
            shoot(screen);
            lastShot = curShot;
        }
    }
    else if (e.type == SDL_MOUSEMOTION) {
        xPos = e.motion.x;
        yPos = e.motion.y;
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
    int temp = numberOfProjectiles / 2;
    for (int i = -numberOfProjectiles / 2; i <= numberOfProjectiles / 2; i++) {
        if (i != 0) {
            SDL_Rect projRect = projectile.getRect();
            SDL_Rect renderquad = { xPos + frameWidth / 2 - projRect.w / 2 + i * PROJECTILES_HORIZONTAL_GAP + i * projRect.w, yPos - projRect.h / 2 + PROJECTILES_VERTICAL_GAP * abs(i), projRect.w, projRect.h};
            projectiles.push_back(renderquad);
        }
        if (i == 0 && numberOfProjectiles % 2 == 1) {
            SDL_Rect projRect = projectile.getRect();
            SDL_Rect renderquad = { xPos + frameWidth / 2 - projRect.w / 2, yPos - projRect.h / 2, projRect.w, projRect.h };
            projectiles.push_back(renderquad);
        }
    }
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
    if (cur - lastHitByEnemy < 1500)
        return false;
    lastHitByEnemy = cur;
    hp--;
    decreaseNumberOfProjectiles();
    decreaseAttackSpeed();
    if (hp <= 0) dead();
    return true;
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