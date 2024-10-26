#include "Enemy.h"
#include <cmath> // For sqrt
#include <stdio.h>
Enemy::Enemy(int x, int y, int width, int height, int hp, int damage, int speed)
    : Character(x, y, width, height, hp, damage, speed) {}

void Enemy::update(SDL_Window* window, int playerX, int playerY) {
    followPlayer(playerX, playerY);

    // Update the rectangle position for rendering
    rect.x = x;
    rect.y = y;
}

void Enemy::followPlayer(int playerX, int playerY) {
    // Calculate direction vector towards the player
    int deltaX = playerX - x;
    int deltaY = playerY - y;

    // Calculate the distance to normalize the direction
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    // Move towards the player if not already there
    if (distance > 0) {
        x += static_cast<int>(speed * (deltaX / distance));
        y += static_cast<int>(speed * (deltaY / distance));
    }
}
void Enemy::takeDamage(int amount) {
    hp -= amount;
}

bool Enemy::isAlive() const {
    return hp > 0;
}
void Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255); // Render enemy as a red rectangle
    SDL_RenderFillRect(renderer, &rect);
}
