#include "src/game/TireObject.h"
#include "src/game/Player.h"
#include "src/game/WallObject.h"
#include "src/game/TruckObject.h"
#include <vector>
#include <memory>
#include <iostream>
#include <random>
#include <SDL.h>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
const float FRICTION = 0.008f;

const int WALLS_THICKNESS = 5;

const int TRUCK_HEIGHT = 250;
const int TIRE_HEIGHT = 25;

const int X_WALL_HEIGHT = WALLS_THICKNESS;
const int X_WALL_WIDTH = WINDOW_WIDTH;
const int Y_WALL_HEIGHT = WINDOW_HEIGHT;
const int Y_WALL_WIDTH = WALLS_THICKNESS;

using namespace std;

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
    SDL_Window* window = SDL_CreateWindow("Crazy Road", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
    SDL_Surface* surface = SDL_LoadBMP("static/road.bmp");

    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, surface);

    Player player({150, 250});

    WallObject wallUp({Y_WALL_WIDTH, 0, X_WALL_WIDTH, X_WALL_HEIGHT});
    WallObject wallBottom({0, WINDOW_HEIGHT-X_WALL_HEIGHT, X_WALL_WIDTH, X_WALL_HEIGHT});
    WallObject wallRight({WINDOW_WIDTH-Y_WALL_WIDTH, 0, Y_WALL_WIDTH, Y_WALL_HEIGHT});
    WallObject wallLeft({0, 0, Y_WALL_WIDTH, Y_WALL_HEIGHT});

    std::vector<std::shared_ptr<TireObject>> tires;
    std::vector<std::shared_ptr<TruckObject>> trucks;

    // glowna petla gry
    bool isRunning = true;

    while (isRunning) {
        frameStart = SDL_GetTicks();

        if (surface == nullptr) {
            cout << "xdkurwa" << endl;
        }

        // obsluga zdarzen
        SDL_Event event;
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
            isRunning = false;
        }

        player.move();

        for (auto& tire : tires) {
            tire->move();
        }

        for (auto& truck_kun : trucks) {
            truck_kun->move();
        }


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

        if (getRandomNumber(0, 100) < 5) {
            int randomX = getRandomNumber(0 + WALLS_THICKNESS, WINDOW_WIDTH - WALLS_THICKNESS);
            auto tire = std::make_shared<TireObject>(Size{randomX, 0, 20, 25});
            int tire_speed = getRandomNumber(2, 4);
            tire->setSpeedY((float)tire_speed);
            tires.push_back(tire);
        }

        if (getRandomNumber(0, 1000) < 5) {
            int randomX = getRandomNumber(0 + WALLS_THICKNESS, WINDOW_WIDTH - WALLS_THICKNESS);
            auto truck_kun = std::make_shared<TireObject>(Size{randomX, 0, 50, 80});
            int truck_speed = getRandomNumber(4, 6);
            truck_kun->setSpeedY((float)truck_speed);
            tires.push_back(truck_kun);
        }

        // usuwanie obiektow ktory wyszly poza ekran


        // wyczyszczenie renderera
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, nullptr, nullptr);

        // rysowanie ścian
        wallUp.draw(renderer, 0, 255, 0);
        wallBottom.draw(renderer, 0, 255, 0);
        wallRight.draw(renderer, 0, 255, 0);
        wallLeft.draw(renderer, 0, 255, 0);

        // rysowanie gracza
        player.draw(renderer);

        // rysowanie opon
        auto iter = tires.begin();
        while (iter != tires.end()) {
            if ((*iter)->getPositionX() < 0 || (*iter)->getPositionX() > WINDOW_WIDTH || (*iter)->getPositionY() < 0 || (*iter)->getPositionY() > WINDOW_HEIGHT) {
                iter = tires.erase(iter);
            } else {
                if (player.checkCollision(**iter)) {
                    cout << "Kolizja! Usuwam obiekt." << endl;
                    player.setSpeedY(4);
                    player.setSpeedX(0);
                    iter = tires.erase(iter);
                    continue; // Przeskocz do następnej iteracji pętli while
                } else {
                    ++iter;
                }
            }
        }

        for (const auto& obj : tires) {
            obj->draw(renderer);
        }

        // rysowanie ciężarówki
        for (const auto& obj : trucks) {
            obj->draw(renderer);
        }

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