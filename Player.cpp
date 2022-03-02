#include "Player.h"

Player::Player() {

    currentFrame = 0;
    xPos = 0;
    yPos = 0;
    frameWidth = 0;
    frameHeight = 0;
    input.left = 0;
    input.right = 0;
    input.up = 0;
    input.down = 0;
    input.jump = 0;
    alive = true;
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

        minXPos = 0;
        maxXPos = WINDOW_WIDTH - frameWidth;

        minYPos = 0;
        maxYPos = WINDOW_HEIGHT - frameHeight * 2 / 3;
    }

}

void Player::show(SDL_Renderer* des) {

    if (input.left == 1) {
        if (currentFrame > 1) currentFrame = 1;
        else currentFrame = 0;
    }
    else if (input.right == 1) {
        if (currentFrame < 3) currentFrame = 3;
        else currentFrame = 4;
    }
    else currentFrame = 2;

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

void Player::handleInput(SDL_Event e, SDL_Renderer* screen) {

    if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
        if (input.keyboardState[SDL_SCANCODE_UP] && !input.keyboardState[SDL_SCANCODE_DOWN]) {
            input.up = 1;
            input.down = 0;
            yPos -= PLAYER_VERTICAL_SPEED;
            if (yPos < minYPos) yPos = minYPos;
        }
        else if (!input.keyboardState[SDL_SCANCODE_UP] && input.keyboardState[SDL_SCANCODE_DOWN]) {
            input.up = 0;
            input.down = 1;
            yPos += PLAYER_VERTICAL_SPEED;
            if (yPos > maxYPos) yPos = maxYPos;
        }
        if (input.keyboardState[SDL_SCANCODE_LEFT] && !input.keyboardState[SDL_SCANCODE_RIGHT]) {
            input.left = 1;
            input.right = 0;
            xPos -= PLAYER_HORIZONTAL_SPEED;
            if (xPos < minXPos) xPos = minXPos;
        }
        else if (!input.keyboardState[SDL_SCANCODE_LEFT] && input.keyboardState[SDL_SCANCODE_RIGHT]) {
            input.left = 0;
            input.right = 1;
            xPos += PLAYER_HORIZONTAL_SPEED;
            if (xPos > maxXPos) xPos = maxXPos;
        }
        else if (!input.keyboardState[SDL_SCANCODE_LEFT] && !input.keyboardState[SDL_SCANCODE_RIGHT]) {
            input.left = 0;
            input.right = 0;
        }
        if (input.keyboardState[SDL_SCANCODE_SPACE]) {
            unsigned int curShot = SDL_GetTicks();
            if (curShot - lastShot >= 300) {
                shoot(screen);
                lastShot = curShot;
            }
        }
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
        projectiles.erase(projectiles.begin() + (i--));
        enemy.dead();
    }
}
