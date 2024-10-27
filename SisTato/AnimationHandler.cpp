#include "AnimationHandler.h"
#include <SDL_image.h>
#include <iostream>

AnimationHandler::AnimationHandler(SDL_Renderer* renderer, const std::string& filePath, SDL_Rect destRect, int numFrames, int animationSpeed, bool isVertical)
    : destRect(destRect), currentFrame(0), lastFrameTime(0), animationSpeed(animationSpeed), totalFrames(numFrames), isVertical(isVertical) {

    destRect.w *= 3;
    destRect.h *= 3;
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load image " << filePath << ": " << IMG_GetError() << std::endl;
        texture = nullptr;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }

    // Set the source rectangle to the size of a single frame
    frameWidth = destRect.w;
    frameHeight = destRect.h;
    srcRect = { 0, 0, frameWidth, frameHeight };
}

AnimationHandler::~AnimationHandler() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void AnimationHandler::update() {
    if (isFinished()) return; // Stop updating if animation is finished

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime >= animationSpeed) {
        lastFrameTime = currentTime;
        currentFrame++;
        if (currentFrame >= totalFrames) currentFrame = totalFrames - 1; // Keep on the last frame

        if (isVertical) {
            srcRect.y = currentFrame * frameHeight;
            srcRect.x = 0;
        }
        else {
            srcRect.x = currentFrame * frameWidth;
            srcRect.y = 0;
        }
    }
}


void AnimationHandler::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    }
}

bool AnimationHandler::isFinished() const {
    return currentFrame >= totalFrames-1;
}
