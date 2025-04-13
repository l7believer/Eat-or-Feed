#pragma once
#include <SDL.h>
#include "Fish.h"
#include "Kethu1.h"

class Game {
public:
    Game();
    ~Game();

    bool init(); //main resources
    void run();
    void close();
    SDL_Rect camera; //Render camera theo cá

private:
    SDL_Window* window; 
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    
    bool quit; //exit
    Fish fish;
	Kethu1 kethu1;

    void handleEvents();
    void render();
    void updateCamera();

};
