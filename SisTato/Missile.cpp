#include "Missile.h"

Missile::Missile(int startX, int startY, int speed, int directionX, int directionY)
    : x(startX), y(startY), speed(speed) {
    // Normalize direction for diagonal movement
    float length = std::sqrt(directionX * directionX + directionY * directionY);
    this->directionX = directionX / length;
    this->directionY = directionY / length;

    rect = { x, y, 10, 10 }; // Set missile size to 10x10 pixels
}

void Missile::update() {
    // Update position based on normalized direction
    x += static_cast<int>(directionX * speed);
    y += static_cast<int>(directionY * speed);
    rect.x = x;
    rect.y = y;
}

void Missile::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for missile
    SDL_RenderFillRect(renderer, &rect);
}

bool Missile::isOffScreen(int windowWidth, int windowHeight) const {
    return x < 0 || x > windowWidth || y < 0 || y > windowHeight;
}
