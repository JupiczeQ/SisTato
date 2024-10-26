#include <SDL.h>
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <cstdlib> // For rand and srand
#include <ctime>   // For time to seed rand

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    uint16_t WINDOW_HEIGHT = 800;
    uint16_t WINDOW_WIDTH = 1200;

    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    Player player(300, 200, 20, 20, 100, 10, 5, 10, 300); // Example player setup with 300ms reload time

    std::vector<Enemy> enemies; // List to store enemies

    Uint32 lastEnemySpawnTime = 0; // Time tracking for enemy spawn
    const int spawnInterval = 5000; // 5 seconds

    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
            player.handleEvent(event);
        }

        // Spawn new enemy every 5 seconds
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastEnemySpawnTime >= spawnInterval) {
            lastEnemySpawnTime = currentTime;

            int x = rand() % WINDOW_WIDTH;
            int y = rand() % WINDOW_HEIGHT; // Spawn at the top of the screen for example

            // Add a new enemy with random position and basic stats
            enemies.emplace_back(x, y, 20, 20, 50, 5, 3); // Example enemy with hp=50, damage=5, speed=3
        }

        // Update player and enemies
        player.update(window);
        for (auto& enemy : enemies) {
            enemy.update(window, player.getX(), player.getY());
        }

        // Clear and render
        SDL_SetRenderDrawColor(renderer, 63, 155, 11, 255); // Green background
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
