#pragma once
#include <SDL.h>
#include "Fish.h"
#include "Kethu1.h"
#include "Kethu2.h"
#include "Kethu3.h"
#include "Kethu4.h"
#include "Kethu5.h"
#include "Kethu6.h"
#include "Kethu7.h"
#include "Kethu8.h"
#include "Kethu9.h"
#include "Kethu10.h"
#include "Kethu11.h"
#include "Kethu12.h"
#include "vector"

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
    SDL_Texture* menuTexture;
	bool inMenu; // Trạng thái menu
    bool quit; //exit
    bool isPaused; // Trạng thái pause
    SDL_Texture* pauseTexture; 
    Fish fish;
    // nhiều kethu cùng loại
    std::vector<Kethu1> enemies1;
    std::vector<Kethu2> enemies2;
    std::vector<Kethu3> enemies3;
    std::vector<Kethu4> enemies4;
    std::vector<Kethu5> enemies5;
    std::vector<Kethu6> enemies6;
    std::vector<Kethu7> enemies7;
    std::vector<Kethu8> enemies8;
    std::vector<Kethu9> enemies9;
    std::vector<Kethu10> enemies10;
    std::vector<Kethu11> enemies11;
    std::vector<Kethu12> enemies12;

    void handleEvents();
    void render();
    void updateCamera();
    void resetGame();
    void renderMenu();
    void renderPause();

};
