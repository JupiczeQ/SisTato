#include <SDL.h>
#include "Player.h"
#include "Enemy.h"
#include "Gun.h"
#include "Utils.h"
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

            enemies.emplace_back(x, y, 20, 20, 20, 3);
        }

        player.update(window);
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
            enemyIt->update(window, player.getX(), player.getY(), enemies);

            // Get missiles from player
            auto& missiles = player.getMissiles();
            bool enemyHit = false;

            for (auto missileIt = missiles.begin(); missileIt != missiles.end(); ) {
                if (Utils::checkCollision(missileIt->getRect(), enemyIt->getRect())) {
                    enemyIt->takeDamage(missileIt->getDamage()); // Apply damage to the enemy

                    // Erase the missile and update the iterator
                    missileIt = missiles.erase(missileIt);
                    enemyHit = true;

                    // If enemy is dead, break out of missile loop to handle enemy removal
                    if (!enemyIt->isAlive()) {
                        break;
                    }
                }
                else {
                    ++missileIt;
                }
            }

            // Remove enemy if it is no longer alive
            if (!enemyIt->isAlive()) {
                enemyIt = enemies.erase(enemyIt);
            }
            else {
                ++enemyIt;
            }
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
