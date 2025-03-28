#include "Game.h"
#include <SDL_image.h>

Game::Game() : window(nullptr), renderer(nullptr), backgroundTexture(nullptr), quit(false) {}

Game::~Game() {
    close();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    window = SDL_CreateWindow("Fish Movement", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 854, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        return false;
    }

    // Load background image
    SDL_Surface* loadedSurface = IMG_Load("C:\\Users\\Nekko Chan\\Desktop\\eatorfeed\\x64\\Debug\\res\\background.png");
    if (loadedSurface == nullptr) {
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    if (backgroundTexture == nullptr) {
        return false;
    }

    // Load fish sprite sheets
    if (!fish.loadSpriteSheet("C:\\Users\\Nekko Chan\\Desktop\\eatorfeed\\x64\\Debug\\res\\player_left.png", "C:\\Users\\Nekko Chan\\Desktop\\eatorfeed\\x64\\Debug\\res\\player_right.png", renderer)) {
        return false;
    }

    // Load enemy sprite sheets
    if (!enemy.loadSpriteSheet("C:\\Users\\Nekko Chan\\Desktop\\eatorfeed\\x64\\Debug\\res\\player_left.png", "C:\\Users\\Nekko Chan\\Desktop\\eatorfeed\\x64\\Debug\\res\\player_right.png", renderer)) {
        return false;
    }

    fish.setPosition(100, 100);
    fish.setDirection(FishDirection::RIGHT);
    fish.setState(FishState::IDLE);

    enemy.setPosition(300, 300);
    enemy.setDirection(EnemyDirection::LEFT);
    enemy.setState(EnemyState::IDLE);

    return true;
}

void Game::run() {
    SDL_Event e;

    while (!quit) {
        handleEvents();
        update();
        render();
    }
}

void Game::close() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        move.handleEvent(e, fish);
    }
}

void Game::update() {
    move.update(fish);
    enemy.update(fish); // Cập nhật vị trí của enemy dựa trên vị trí của fish
}

void Game::render() {
    SDL_RenderClear(renderer);

    // Render background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    move.render(renderer, fish);
    enemy.render(renderer); // Render enemy

    SDL_RenderPresent(renderer);
}



