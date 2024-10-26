#include "Player.h"

Player::Player(int x, int y, int width, int height, int hp, int speed, int missileSpeed, int reloadTime, int damage)
    : Character(x, y, width, height, hp, speed), gun(missileSpeed, reloadTime, damage) {
}

void Player::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_w: moveUp = true; break;
        case SDLK_s: moveDown = true; break;
        case SDLK_a: moveLeft = true; break;
        case SDLK_d: moveRight = true; break;
        case SDLK_UP: shootingUp = true; break;
        case SDLK_DOWN: shootingDown = true; break;
        case SDLK_LEFT: shootingLeft = true; break;
        case SDLK_RIGHT: shootingRight = true; break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_w: moveUp = false; break;
        case SDLK_s: moveDown = false; break;
        case SDLK_a: moveLeft = false; break;
        case SDLK_d: moveRight = false; break;
        case SDLK_UP: shootingUp = false; break;
        case SDLK_DOWN: shootingDown = false; break;
        case SDLK_LEFT: shootingLeft = false; break;
        case SDLK_RIGHT: shootingRight = false; break;
        }
    }
}

void Player::update(SDL_Window* window) {
    Character::update(window);
    if (shootingUp && shootingLeft) gun.shoot(x + width / 2, y + height / 2, -1, -1);
    else if (shootingUp && shootingRight) gun.shoot(x + width / 2, y + height / 2, 1, -1);
    else if (shootingDown && shootingLeft) gun.shoot(x + width / 2, y + height / 2, -1, 1);
    else if (shootingDown && shootingRight) gun.shoot(x + width / 2, y + height / 2, 1, 1);
    else if (shootingUp) gun.shoot(x + width / 2, y + height / 2, 0, -1);
    else if (shootingDown) gun.shoot(x + width / 2, y + height / 2, 0, 1);
    else if (shootingLeft) gun.shoot(x + width / 2, y + height / 2, -1, 0);
    else if (shootingRight) gun.shoot(x + width / 2, y + height / 2, 1, 0);

    gun.update(window);
}

void Player::render(SDL_Renderer* renderer) {
    Character::render(renderer);
    gun.render(renderer);
}
