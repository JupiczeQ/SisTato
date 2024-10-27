#ifndef DEATH_ANIMATION_H
#define DEATH_ANIMATION_H

#include <SDL.h>
#include <SDL_image.h>

class DeathAnimation {
public:
    DeathAnimation(SDL_Renderer* renderer, int x, int y);
    ~DeathAnimation();
    bool isFinished() const;
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Texture* texture;
    int x, y;
    int frameWidth = 20;
    int frameHeight = 20;
    int currentFrame;
    int maxFrames;

    // Rectangle to define source and destination for each frame
    SDL_Rect srcRect;
    SDL_Rect destRect;

    // Variables to control animation speed
    Uint32 lastUpdate;  // Time of the last frame update
    int frameDelay;     // Delay in milliseconds between frames
};

#endif
