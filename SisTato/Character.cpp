#include "Character.h"
#include <cmath>

Character::Character(int x, int y, int width, int height, int hp, float speed)
    : x(x), y(y), width(width), height(height), hp(hp), speed(speed) {
    rect = { x, y, width, height };
}

int Character::getX() const {
    return x;
}

int Character::getY() const {
    return y;
}

void Character::update(SDL_Window* window) {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float adjustedSpeed = speed;
    bool diagonal = (moveUp || moveDown) && (moveLeft || moveRight);
    if (diagonal)
        adjustedSpeed /= std::sqrt(2);

    if (moveUp) {
        y -= adjustedSpeed;
        if (y < 0) y = 0;
    }
    if (moveDown) {
        y += adjustedSpeed;
        if (y + height > windowHeight) y = windowHeight - height;
    }
    if (moveLeft) {
        x -= adjustedSpeed;
        if (x < 0) x = 0;
    }
    if (moveRight) {
        x += adjustedSpeed;
        if (x + width > windowWidth) x = windowWidth - width;
    }

    rect.x = x;
    rect.y = y;
}

void Character::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Character::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

bool Character::isAlive() const {
    return hp > 0;
}
