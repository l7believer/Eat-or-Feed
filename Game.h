#pragma once
#include <SDL.h>
#include "Fish.h"
#include "Move.h"
#include "Enemy.h"

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
    Enemy enemy; // Thêm đối tượng Enemy
    Move move;
    bool quit;
};



