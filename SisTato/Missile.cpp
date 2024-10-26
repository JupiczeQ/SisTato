#include "Missile.h"

Missile::Missile(int startX, int startY, int speed, int directionX, int directionY, int damage)
    : x(startX), y(startY), speed(speed), damage(damage) {
    // Normalize direction for diagonal movement
    float length = std::sqrt(directionX * directionX + directionY * directionY);
    this->directionX = directionX / length;
    this->directionY = directionY / length;

    rect = { x, y, 10, 10 }; // Set missile size to 10x10 pixels
}

SDL_Rect Missile::getRect() {
    return rect;
}

int Missile::getDamage() {
    return damage;
}

void Missile::update() {
    // Update position based on normalized direction
    x += static_cast<int>(directionX * speed);
    y += static_cast<int>(directionY * speed);
    rect.x = x;
    rect.y = y;
}

void Missile::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color for missile
    SDL_RenderFillRect(renderer, &rect);
}

bool Missile::isOffScreen(int windowWidth, int windowHeight) const {
    return x < 0 || x > windowWidth || y < 0 || y > windowHeight;
}
