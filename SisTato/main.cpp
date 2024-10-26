#include <SDL.h>
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    uint16_t WINDOW_HEIGHT = 800;
    uint16_t WINDOW_WIDTH = 1200;

    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    Player player(300, 200, 20, 20, 100, 5, 10, 300, 10); // Updated to match the new constructor

    std::vector<Enemy> enemies;

    Uint32 lastEnemySpawnTime = 0;
    const int spawnInterval = 2000;

    srand(static_cast<unsigned int>(time(0)));

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
            player.handleEvent(event);
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastEnemySpawnTime >= spawnInterval) {
            lastEnemySpawnTime = currentTime;

            int x = rand() % WINDOW_WIDTH;
            int y = rand() % WINDOW_HEIGHT;

            enemies.emplace_back(x, y, 20, 20, 50, 3);
        }

        player.update(window);
        for (auto& enemy : enemies) {
            enemy.update(window, player.getX(), player.getY(), enemies);
        }

        SDL_SetRenderDrawColor(renderer, 63, 155, 11, 255);
        SDL_RenderClear(renderer);

        player.render(renderer);
        for (auto& enemy : enemies) {
            enemy.render(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
