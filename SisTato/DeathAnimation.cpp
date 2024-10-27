#include "DeathAnimation.h"

DeathAnimation::DeathAnimation(SDL_Renderer* renderer, int x, int y)
    : x(x), y(y), currentFrame(0), maxFrames(3) {

    // Load the spritesheet (replace "death_animation.png" with the actual file path)
    SDL_Surface* tempSurface = IMG_Load("Sprites\\Explosion.png");
    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    // Set the source rectangle for each frame in the sprite
    srcRect = { 0, 0, frameWidth, frameHeight };

    // Scale the destination rectangle to make the animation appear larger (e.g., 40x40)
    destRect = { x-10, y-10, frameWidth * 2, frameHeight * 2 };

    // Set initial frame delay (e.g., 200ms per frame)
    frameDelay = 100;
    lastUpdate = SDL_GetTicks();
}

DeathAnimation::~DeathAnimation() {
    SDL_DestroyTexture(texture);
}

bool DeathAnimation::isFinished() const {
    return currentFrame >= maxFrames;
}

void DeathAnimation::update() {
    // Only update frame if enough time has passed
    Uint32 now = SDL_GetTicks();
    if (now - lastUpdate >= frameDelay) {
        if (currentFrame < maxFrames) {
            srcRect.y = currentFrame * frameHeight; // Move to next frame
            currentFrame++;
        }
        lastUpdate = now; // Reset the timer for the next frame
    }
}

void DeathAnimation::render(SDL_Renderer* renderer) {
    if (currentFrame < maxFrames) {
        SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    }
}
