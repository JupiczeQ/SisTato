#include "Enemy.h"
#include <cmath> // For sqrt
#include <stdio.h>
#include <vector>
Enemy::Enemy(int x, int y, int width, int height, int hp, int damage, int speed)
    : Character(x, y, width, height, hp, damage, speed) {}

void Enemy::update(SDL_Window* window, int playerX, int playerY, std::vector<Enemy>& enemies) {
    followPlayer(playerX, playerY);
    avoidCollisions(enemies);

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

void Enemy::avoidCollisions(std::vector<Enemy>& enemies) {
    const float collisionRadius = 30.0f;
    const float repulsionStrength = 1.0f;

    for (auto& other : enemies) {
        if (&other == this) continue;

        int deltaX = x - other.x;
        int deltaY = y - other.y;
        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        if (distance < collisionRadius && distance > 0) {
            float repulsionFactor = repulsionStrength / distance;
            x += static_cast<int>(repulsionFactor * deltaX);
            y += static_cast<int>(repulsionFactor * deltaY);
        }
    }
}

void Enemy::takeDamage(int amount) {
    hp -= amount;
}

bool Enemy::isAlive() const {
    return hp > 0;
}
void Enemy::render(SDL_Renderer* renderer) {
    // Render the enemy as a filled red rectangle
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255); // Red fill
    SDL_RenderFillRect(renderer, &rect);

    // Render the outline of the enemy rectangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black outline
    SDL_RenderDrawRect(renderer, &rect);
}