#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include <SDL.h>

class Enemy : public Character {
public:
    Enemy(int x, int y, int width, int height, int hp, int damage, int speed);
    void update(SDL_Window* window, int playerX, int playerY); // Override to follow player
    void render(SDL_Renderer* renderer) override;

    // Handle damage and check if the enemy is alive
    void takeDamage(int amount);
    bool isAlive() const;

private:
    void followPlayer(int playerX, int playerY);
};

#endif