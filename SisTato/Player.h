#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Gun.h"

class Player : public Character {
public:
    Player(int x, int y, int width, int height, int hp, int speed, int missileSpeed, int reloadTime, int damage);
    void handleEvent(SDL_Event& event) override;
    void update(SDL_Window* window) override;
    void render(SDL_Renderer* renderer) override;
    std::vector<Missile>& getMissiles();

private:
    Gun gun;
    bool shootingUp = false;
    bool shootingDown = false;
    bool shootingLeft = false;
    bool shootingRight = false;
};

#endif
