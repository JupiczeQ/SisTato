#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include <SDL.h>
#include <vector>

#include "DeathAnimation.h"
#include <memory>

class Enemy : public Character {
public:
    Enemy(int x, int y, int width, int height, int hp, int speed, SDL_Renderer* renderer);
    void update(SDL_Window* window, int playerX, int playerY, std::vector<Enemy>& enemies);
    void render(SDL_Renderer* renderer) override;

    void takeDamage(int amount);
    bool isAlive() const;
    bool isDead() const;  // Getter for isDead
    bool isDeathAnimationFinished() const;  // Getter for checking if the animation is done

    SDL_Rect getRect() const;

private:
    bool isDeadFlag;
    SDL_Renderer* renderer; // Store renderer here
    std::unique_ptr<DeathAnimation> deathAnimation;
    void followPlayer(int playerX, int playerY);
    void avoidCollisions(std::vector<Enemy>& enemies);
};

#endif
