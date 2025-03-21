#pragma once
#include <SDL.h>
#include "Fish.h"
#include "Move.h"

class Game {
public:
    Game();
    ~Game();
    bool init();
    void run();
    void close();

private:
    void handleEvents();
    void update();
    void render();

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    Fish fish;
    Move move;
    bool quit;
};








