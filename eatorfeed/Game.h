//#pragma once
//#include <SDL.h>
//#include "Fish.h"
//
//class Game {
//public:
//    Game();
//    ~Game();
//
//    bool init();
//    void run();
//    void close();
//    SDL_Rect camera;
//
//private:
//    SDL_Window* window;
//    SDL_Renderer* renderer;
//    SDL_Texture* backgroundTexture;
//    bool quit;
//    Fish fish;
//
//    void handleEvents();
//    void render();
//};

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

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    SDL_Rect camera; // Camera để theo dõi vị trí
    bool quit;
    Fish fish;

    void handleEvents();
    void render();
    void updateCamera(); // Cập nhật camera
};
