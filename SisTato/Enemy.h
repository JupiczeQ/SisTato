#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include <SDL.h>
#include <vector>

class Enemy : public Character {
public:
    Enemy(int x, int y, int width, int height, int hp, int speed);
    void update(SDL_Window* window, int playerX, int playerY, std::vector<Enemy>& enemies); // Override to follow player
    void render(SDL_Renderer* renderer) override;

    // Handle damage and check if the enemy is alive
    void takeDamage(int amount);
    bool isAlive() const;
    
    SDL_Rect getRect() const;

private:
    void followPlayer(int playerX, int playerY);
    void avoidCollisions(std::vector<Enemy>& enemies);
};

#endif
