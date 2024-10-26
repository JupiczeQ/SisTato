#ifndef GUN_H
#define GUN_H

#include "Missile.h"
#include <SDL.h>
#include <vector>

class Gun {
public:
    Gun(int missileSpeed, int reloadTime, int damage);
    void shoot(int startX, int startY, int directionX, int directionY);
    void update(SDL_Window* window);
    void render(SDL_Renderer* renderer);
    int getDamage() const;  // Add this getter for damage

private:
    std::vector<Missile> missiles;
    int missileSpeed;
    int reloadTime;
    int damage;  // Damage dealt per missile
    Uint32 lastShotTime;
};

#endif
