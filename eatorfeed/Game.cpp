#include "Game.h"
#include <SDL_image.h>
#include "Constants.h"

Game::Game() : window(nullptr), renderer(nullptr), backgroundTexture(nullptr), quit(false) {}

Game::~Game() {
    close();
}

bool Game::init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Fish Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_FULLSCREEN); // Toàn màn hình

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_ShowCursor(SDL_DISABLE); // Ẩn chuột

    SDL_Surface* bg = IMG_Load("res/eq.png");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);

    fish.loadSpriteSheet("res/player_left.png", "res/player_right.png", renderer);

    return true;
}



void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) quit = true;
        else if (e.type == SDL_MOUSEMOTION) {
            fish.updatePosition(e.motion.x, e.motion.y);
        }
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    SDL_Rect bgDestRect = { 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, &bgDestRect); // Vẽ full background
    fish.render(renderer); // Vẽ cá

    SDL_RenderPresent(renderer);
}




void Game::run() {
    while (!quit) {
        handleEvents();
        render();
    }
}


void Game::close() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


