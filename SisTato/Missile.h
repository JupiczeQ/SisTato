#ifndef MISSILE_H
#define MISSILE_H

#include <SDL.h>
#include <cmath>

class Missile {
public:
    Missile(int startX, int startY, int speed, int directionX, int directionY);
    void update();
    void render(SDL_Renderer* renderer);
    bool isOffScreen(int windowWidth, int windowHeight) const;

private:
    int x, y; // Position
    int speed;
    float directionX, directionY; // Movement direction, normalized for diagonals
    SDL_Rect rect; // Rectangle for rendering
};

#endif
