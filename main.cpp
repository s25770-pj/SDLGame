#include "src/game/IceBlock.h"
#include "src/game/Player.h"
#include <vector>
#include <memory>
#include <iostream>
#include <random>
#include <SDL.h>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
int BASE_PLAYER_WIDTH = 20;
int COLUMN_WIDTH = 150;
float COLUMN_SPEED = 100.0f; // predkosc opadania kolumn
int COLUMN_SPAWN_FREQUENCY = 1500; // czestotliwosc generowania kolumn (w ms)
float INITIAL_COLUMN_SPEED = 1.0f; // predkosc opadania poczatkowej kolumny


// Funkcja generująca losową liczbę z zakresu min do max
int getRandomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

// Struktura reprezentująca kolumnę
struct Column {
    std::unique_ptr<GameObject> object;
    float speed;
    Column(std::unique_ptr<GameObject> obj, float spd) : object(std::move(obj)), speed(spd) {}
};

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

    std::vector<Column> columns;
    int score = 0;

    // dodawanie poczatkowej kolumny
    columns.emplace_back(std::make_unique<IceBlock>(0, WINDOW_HEIGHT-20, WINDOW_WIDTH), INITIAL_COLUMN_SPEED);

    // glowna petla gry
    bool isRunning = true;
    Uint32 lastFrameTime = SDL_GetTicks();
    Uint32 lastSpawnTime = SDL_GetTicks();

    while (isRunning) {
        // obsluga zdarzen
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // aktualizacja czasu do ostatniej klatki
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f; // Zamiana na sekundy
        lastFrameTime = currentFrameTime;

        // start generowania kolumn po okreslonym czasie
        if (currentFrameTime - lastSpawnTime > COLUMN_SPAWN_FREQUENCY) {
            columns.emplace_back(std::make_unique<IceBlock>(getRandomNumber(20, WINDOW_WIDTH - COLUMN_WIDTH - 20), 0, COLUMN_WIDTH), COLUMN_SPEED);
            lastSpawnTime = currentFrameTime;

            score += 10;
        }

        // aktualizacja obiektow w grze
        for (auto& column : columns) {
            auto& obj = column.object;
            obj->update(deltaTime);

            // opadanie kolumny
            obj->move(0, column.speed * deltaTime);

            // usuwanie kolumn poza ekranem
            if (obj->getPositionY() > WINDOW_HEIGHT) {
                obj.reset(); // zwolnienie pamieci
            }
        }

        // usuwanie kolumn o pustych wskaznikach
        columns.erase(std::remove_if(columns.begin(), columns.end(), [](const Column& column) { return !column.object; }), columns.end());

        // wyczyszczenie renderera
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);

        // rysowanie obiektow
        for (const auto& column : columns) {
            column.object->draw(renderer);
        }

        // wyswietlanie aktualnej klatki
        SDL_RenderPresent(renderer);
    }

    // zwalnianie zasobow
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}