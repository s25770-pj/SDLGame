#include "src/game/IceBlock.h"
#include "src/game/Player.h"
#include <vector>
#include <memory>
#include <iostream>
#include <SDL.h>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
int BASE_PLAYER_WIDTH = 20;

int main(int argc, char* argv[]) {
    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Nie udało się zainicjalizować SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // init okno gry
    SDL_Window* window = SDL_CreateWindow("Snow Tower", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Nie udało się stworzyć okna gry: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // init render
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Nie udało się stworzyć renderera: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // init obiektu gry
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    gameObjects.push_back(std::make_unique<IceBlock>(100.0f, 100.0f, 150));
    gameObjects.push_back(std::make_unique<IceBlock>(200.0f, 200.0f, 150));
    gameObjects.push_back(std::make_unique<IceBlock>(300.0f, 300.0f, 150));
    gameObjects.push_back(std::make_unique<IceBlock>(400.0f, 400.0f, 150));
    gameObjects.push_back(std::make_unique<IceBlock>(400.0f, 500.0f, 150));
    gameObjects.push_back(std::make_unique<IceBlock>(500.0f, 250.0f, 150));
    gameObjects.push_back(std::make_unique<IceBlock>(0.0f, 580.0f, 800));

    auto player = std::make_unique<Player>(150.0f, 150.0f, BASE_PLAYER_WIDTH);
    player->setGravity(9.8f);
    gameObjects.push_back(std::move(player));

    // główna pętla gry
    bool isRunning = true;
    Uint32 lastFrameTime = SDL_GetTicks();

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        // w lewo
                        if (gameObjects.back()->getPositionX() > 0) {
                            gameObjects.back()->move(-5, 0);
                        }
                        break;
                    case SDLK_RIGHT:
                        // w prawo
                        if (gameObjects.back()->getPositionX() < (float)WINDOW_WIDTH-(float)BASE_PLAYER_WIDTH) {
                            gameObjects.back()->move(5, 0);
                        }
                        break;
                    case SDLK_UP:
                        // skok
                        break;
                    default:
                        break;
                }
            }
        }

        // aktualizacja czasu od ostatniej klatki
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;

        for (auto& obj : gameObjects) {
            obj->update(deltaTime);
        }

        for (auto& block : gameObjects) {
            if (auto iceBlock = dynamic_cast<IceBlock*>(block.get())) {
                auto player = dynamic_cast<Player*>(gameObjects.back().get());
                if (player && player->checkCollision(*iceBlock)) {
                    player->setGravity(0.0f);
                } else {
                    player->setGravity(20.0f);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);

        // rysowanie obiektów
        for (const auto& obj : gameObjects) {
            obj->draw(renderer);
        }

        // wyświetlanie aktualnej klatki
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
