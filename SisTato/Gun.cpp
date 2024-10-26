#include "Gun.h"
#include <algorithm>

Gun::Gun(int missileSpeed, int reloadTime, int damage)
    : missileSpeed(missileSpeed), reloadTime(reloadTime), damage(damage), lastShotTime(0) {}

void Gun::shoot(int startX, int startY, int directionX, int directionY) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastShotTime >= reloadTime) {
        missiles.emplace_back(startX, startY, missileSpeed, directionX, directionY);
        lastShotTime = currentTime;
    }
}

void Gun::update(SDL_Window* window) {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    for (auto it = missiles.begin(); it != missiles.end();) {
        it->update();
        if (it->isOffScreen(windowWidth, windowHeight)) {
            it = missiles.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Gun::render(SDL_Renderer* renderer) {
    for (Missile& missile : missiles) {
        missile.render(renderer);
    }
}

int Gun::getDamage() const {
    return damage;
}
