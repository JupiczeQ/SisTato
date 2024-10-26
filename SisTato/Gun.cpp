#include "Gun.h"
#include <algorithm> // For std::remove_if

Gun::Gun(int missileSpeed, int reloadTime)
    : missileSpeed(missileSpeed), reloadTime(reloadTime), lastShotTime(0) {}

void Gun::shoot(int startX, int startY, int directionX, int directionY) {
    // Get the current time
    Uint32 currentTime = SDL_GetTicks();

    // Only allow shooting if enough time has passed since the last shot
    if (currentTime - lastShotTime >= reloadTime) {
        missiles.emplace_back(startX, startY, missileSpeed, directionX, directionY);
        lastShotTime = currentTime; // Reset last shot time
    }
}

void Gun::update(SDL_Window* window) {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Update each missile and remove any that go off-screen
    for (auto it = missiles.begin(); it != missiles.end();) {
        it->update();
        if (it->isOffScreen(windowWidth, windowHeight)) {
            it = missiles.erase(it); // Remove missile if it's off-screen
        } else {
            ++it;
        }
    }
}

void Gun::render(SDL_Renderer* renderer) {
    for (Missile& missile : missiles) {
        missile.render(renderer);
    }
}
