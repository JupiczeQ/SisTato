#ifndef MISSILE_H
#define MISSILE_H

#include <SDL.h>
#include <cmath>

class Missile {
public:
    Missile(int startX, int startY, int speed, int directionX, int directionY, int damage);
    void update();
    void render(SDL_Renderer* renderer);
    bool isOffScreen(int windowWidth, int windowHeight) const;
    SDL_Rect getRect();
    int getDamage();

private:
    int x, y; // Position
    int speed;
    int damage;
    float directionX, directionY; // Movement direction, normalized for diagonals
    SDL_Rect rect; // Rectangle for rendering
};

#endif
