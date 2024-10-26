#pragma once
// Utils.h
#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>

namespace Utils {
    bool checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);
}

#endif // UTILS_H
