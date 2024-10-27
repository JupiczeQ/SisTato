#include "Enemy.h"
#include <cmath> // For sqrt
#include <stdio.h>
#include <vector>
Enemy::Enemy(int x, int y, int width, int height, int hp, int speed, SDL_Renderer* renderer)
    : Character(x, y, width, height, hp, speed), isDeadFlag(false), renderer(renderer), deathAnimation(nullptr) {}

void Enemy::update(SDL_Window* window, int playerX, int playerY, std::vector<Enemy>& enemies) {
    if (!isDeadFlag) {
        followPlayer(playerX, playerY);
        avoidCollisions(enemies);
    }
    else if (deathAnimation) {
        deathAnimation->update();
    }
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
    const float repulsionStrength = 1.1f;

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
    if (hp <= 0 && !isDeadFlag) {
        isDeadFlag = true;
        deathAnimation = std::make_unique<DeathAnimation>(renderer, x, y);
    }
}

bool Enemy::isAlive() const {
    return hp > 0;
}

bool Enemy::isDead() const {
    return isDeadFlag;
}

bool Enemy::isDeathAnimationFinished() const {
    return deathAnimation && deathAnimation->isFinished();
}

SDL_Rect Enemy::getRect() const {
    return rect;
}

void Enemy::render(SDL_Renderer* renderer) {
    if (!isDeadFlag) {
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    else if (deathAnimation) {
        deathAnimation->render(renderer);
    }
}