#include "src/game/TireObject.h"
#include "src/game/Player.h"
#include "src/game/WallObject.h"
#include <vector>
#include <memory>
#include <iostream>
#include <random>
#include <SDL.h>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
const float FRICTION = 0.008f;

const int WALLS_THICKNESS = 5;

const int X_WALL_HEIGHT = WALLS_THICKNESS;
const int X_WALL_WIDTH = WINDOW_WIDTH;
const int Y_WALL_HEIGHT = WINDOW_HEIGHT;
const int Y_WALL_WIDTH = WALLS_THICKNESS;

int FPS = 60;
int frameDelay = 1000 / FPS;

Uint32 frameStart;
int frameTime;

// Funkcja generująca losową liczbę z zakresu min do max
int getRandomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

int main(int argc, char* argv[]) {
    // inicjalizacja sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Nie udało się zainicjalizować SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // tworzenie okna gry
    SDL_Window* window = SDL_CreateWindow("Snow Tower", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Nie udało się stworzyć okna gry: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // tworzenie renderera
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Nie udało się stworzyć renderera: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Player player({150, 250});

    WallObject wallUp({Y_WALL_WIDTH, 0, X_WALL_WIDTH, X_WALL_HEIGHT});
    WallObject wallBottom({0, WINDOW_HEIGHT-X_WALL_HEIGHT, X_WALL_WIDTH, X_WALL_HEIGHT});
    WallObject wallRight({WINDOW_WIDTH-Y_WALL_WIDTH, 0, Y_WALL_WIDTH, Y_WALL_HEIGHT});
    WallObject wallLeft({0, 0, Y_WALL_WIDTH, Y_WALL_HEIGHT});

    // glowna petla gry
    bool isRunning = true;

    while (isRunning) {
        frameStart = SDL_GetTicks();

        // obsluga zdarzen
        SDL_Event event;
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
            isRunning = false;
        }

        player.move((int)player.getSpeedX(), (int)player.getSpeedY());

        if (player.checkCollision(wallUp) || player.checkCollision(wallBottom) || player.checkCollision(wallRight) || player.checkCollision(wallLeft)) {
            std::cout << "oj jest kolizja" << std::endl;
            player.setSpeedX(player.getSpeedX());
            player.setSpeedY(-player.getSpeedY());
        }

        if (player.getSpeedY() > 0) {
            player.setSpeedY(std::max(player.getSpeedY() - FRICTION, 0.0f));
        } else if (player.getSpeedY() < 0) {
            player.setSpeedY(std::min(player.getSpeedY() + FRICTION, 0.0f));
        }
        if (player.getSpeedX() > 0) {
            player.setSpeedX(std::max(player.getSpeedX() - FRICTION, 0.0f));
        } else if (player.getSpeedX() < 0) {
            player.setSpeedX(std::min(player.getSpeedX() + FRICTION, 0.0f));
        }

//        std::cout << "|speedX" << player.getSpeedX() << "|SpeedY" << player.getSpeedY() << std::endl;

        const Uint8* keystate = SDL_GetKeyboardState(nullptr);
        if (keystate[SDL_SCANCODE_LEFT]) {
            player.accelerateLeft();
        }
        if (keystate[SDL_SCANCODE_RIGHT]) {
            player.accelerateRight();
        }
        if (keystate[SDL_SCANCODE_UP]) {
            player.accelerateUp();
        }
        if (keystate[SDL_SCANCODE_DOWN]) {
            player.accelerateDown();
        }

        // wyczyszczenie renderera
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);

        // rysowanie gracza
        player.draw(renderer);
        wallUp.draw(renderer, 0, 255, 0);
        wallBottom.draw(renderer, 0, 255, 0);
        wallRight.draw(renderer, 0, 255, 0);
        wallLeft.draw(renderer, 0, 255, 0);

        // wyswietlanie aktualnej klatki
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // zwalnianie zasobow
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}