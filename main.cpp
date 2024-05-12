#include "src/game/IceBlock.h"
#include <vector>
#include <memory>
#include <iostream>
#include <SDL.h>

int main(int argc, char* argv []) {
    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Nie udało się zainicjalizować SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // init okno gry
    SDL_Window* window = SDL_CreateWindow("Snow Tower", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
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
    gameObjects.push_back(std::make_unique<IceBlock>(100.0f, 100.0f, 50));

    // główna pętla gry
    bool isRunning = true;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        // czyszczenie ekranu
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // rysowanie obiektów
        for (const auto& obj : gameObjects) {
            obj->draw(renderer);
        }

        // wyswietlanie aktualnej klatki
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}