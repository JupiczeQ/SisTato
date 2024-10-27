#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include <SDL.h>
#include <string>

class AnimationHandler {
public:
    AnimationHandler(SDL_Renderer* renderer, const std::string& filePath, SDL_Rect destRect, int numFrames, int animationSpeed, bool isVertical = false);
    ~AnimationHandler();

    void update();
    void render(SDL_Renderer* renderer);
    bool isFinished() const;

private:
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;         // Holds the position and size for rendering
    int frameWidth, frameHeight;
    int currentFrame;
    int totalFrames;
    Uint32 lastFrameTime;
    int animationSpeed;
    bool isVertical;
};

#endif // ANIMATION_HANDLER_H
