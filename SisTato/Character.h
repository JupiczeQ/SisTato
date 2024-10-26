#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>

class Character {
public:
    Character(int x, int y, int width, int height, int hp, int damage, float speed);

    virtual void handleEvent(SDL_Event& event) {}
    virtual void update(SDL_Window* window);
    virtual void render(SDL_Renderer* renderer);

    int getX() const;
    int getY() const;
    
    void takeDamage(int amount);
    bool isAlive() const;

protected:
    int x, y;
    int width, height;
    int hp;
    int damage;
    float speed;
    SDL_Rect rect;

    // Movement flags
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;
};

#endif
