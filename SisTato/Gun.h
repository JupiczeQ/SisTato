#ifndef GUN_H
#define GUN_H

#include "Missile.h"
#include <SDL.h>
#include <vector>

class Gun {
public:
    Gun(int missileSpeed, int reloadTime);
    void shoot(int startX, int startY, int directionX, int directionY);
    void update(SDL_Window* window);
    void render(SDL_Renderer* renderer);

private:
    std::vector<Missile> missiles; // List of active missiles
    int missileSpeed;               // Speed of each missile
    int reloadTime;                 // Time in milliseconds between shots
    Uint32 lastShotTime;            // Timestamp of the last shot fired
};

#endif
