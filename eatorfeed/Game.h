#pragma once
#include <SDL.h>
#include "Fish.h"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void close();
    SDL_Rect camera;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    bool quit;
    Fish fish;

    void handleEvents();
    void render();
};

