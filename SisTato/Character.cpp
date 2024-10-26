#include "Character.h"
#include <cmath>

Character::Character(int x, int y, int width, int height, int hp, int damage, float speed)
    : x(x), y(y), width(width), height(height), hp(hp), damage(damage), speed(speed) {
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

    // Apply movement based on flags with boundary checks and edge snapping
    if (moveUp) {
        y -= adjustedSpeed;
        if (y < 0) y = 0;  // Snap to top edge if crossing
    }
    if (moveDown) {
        y += adjustedSpeed;
        if (y + height > windowHeight) y = windowHeight - height; // Snap to bottom edge if crossing
    }
    if (moveLeft) {
        x -= adjustedSpeed;
        if (x < 0) x = 0;  // Snap to left edge if crossing
    }
    if (moveRight) {
        x += adjustedSpeed;
        if (x + width > windowWidth) x = windowWidth - width; // Snap to right edge if crossing
    }

    // Update the rectangle position
    rect.x = x;
    rect.y = y;
}

void Character::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Render color for character
    SDL_RenderFillRect(renderer, &rect);
}

void Character::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

bool Character::isAlive() const {
    return hp > 0;
}
