#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Gun.h"

class Player : public Character {
public:

    Player(int x, int y, int width, int height, int hp, int damage, int speed, int missileSpeed, int reloadTime);
    void handleEvent(SDL_Event& event) override;
    void update(SDL_Window* window) override;
    void render(SDL_Renderer* renderer) override;

private:
    Gun gun; // Gun for handling missiles

    // Flags to track arrow key states for automatic shooting
    bool shootingUp = false;
    bool shootingDown = false;
    bool shootingLeft = false;
    bool shootingRight = false;
};

#endif
