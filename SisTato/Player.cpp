#include "Player.h"

Player::Player(int x, int y, int width, int height, int hp, int damage, int speed, int missileSpeed, int reloadTime)
    : Character(x, y, width, height, hp, damage, speed), gun(missileSpeed, reloadTime) {
}

void Player::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_w: moveUp = true; break;
        case SDLK_s: moveDown = true; break;
        case SDLK_a: moveLeft = true; break;
        case SDLK_d: moveRight = true; break;

            // Arrow keys to start shooting in the desired direction
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

            // Arrow keys to stop shooting in the desired direction
        case SDLK_UP: shootingUp = false; break;
        case SDLK_DOWN: shootingDown = false; break;
        case SDLK_LEFT: shootingLeft = false; break;
        case SDLK_RIGHT: shootingRight = false; break;
        }
    }
}

void Player::update(SDL_Window* window) {
    // Update player movement
    Character::update(window);

    // Determine shooting direction based on arrow keys pressed
    if (shootingUp && shootingLeft) gun.shoot(x + width / 2, y + height / 2, -1, -1);      // Up-Left
    else if (shootingUp && shootingRight) gun.shoot(x + width / 2, y + height / 2, 1, -1);  // Up-Right
    else if (shootingDown && shootingLeft) gun.shoot(x + width / 2, y + height / 2, -1, 1); // Down-Left
    else if (shootingDown && shootingRight) gun.shoot(x + width / 2, y + height / 2, 1, 1); // Down-Right
    else if (shootingUp) gun.shoot(x + width / 2, y + height / 2, 0, -1);                   // Up
    else if (shootingDown) gun.shoot(x + width / 2, y + height / 2, 0, 1);                  // Down
    else if (shootingLeft) gun.shoot(x + width / 2, y + height / 2, -1, 0);                 // Left
    else if (shootingRight) gun.shoot(x + width / 2, y + height / 2, 1, 0);                 // Right

    // Update gun and missiles
    gun.update(window);
}

void Player::render(SDL_Renderer* renderer) {
    Character::render(renderer);

    // Render missiles through gun
    gun.render(renderer);
}
