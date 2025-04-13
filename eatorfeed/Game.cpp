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
        SDL_WINDOW_FULLSCREEN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_ShowCursor(SDL_DISABLE);

    SDL_Surface* bg = IMG_Load("res/eq.png");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);

    // Khởi tạo camera
    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	kethu1.loadSpriteSheet("res/Kethu1_left.png", "res/Kethu1_right.png", renderer);
    fish.loadSpriteSheet("res/player_left.png", "res/player_right.png", renderer);

    return true;
}



void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) quit = true;
    }

    // Lấy tọa độ chuột
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Chuyển đổi tọa độ chuột sang hệ tọa độ của background
    mouseX += camera.x;
    mouseY += camera.y;

	kethu1.updatePosition();
    fish.updatePosition(mouseX, mouseY);
}

void Game::render() {
    SDL_RenderClear(renderer);

    // Vẽ background theo camera
    SDL_RenderCopy(renderer, backgroundTexture, &camera, nullptr);

	kethu1.render(renderer, camera);
    fish.render(renderer, camera);

    SDL_RenderPresent(renderer);
}

void Game::run() {
    while (!quit) {
        handleEvents();
        updateCamera();
        render();
        SDL_Delay(16); //FPS
    }
}

//void Game::close() {
//    SDL_DestroyTexture(backgroundTexture);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    IMG_Quit();
//    SDL_Quit();
//}
void Game::close() {
    // Giải phóng các tài nguyên khác
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}



void Game::updateCamera() {
    // Lấy vị trí của cá
    float fishX = fish.getX();
    float fishY = fish.getY();

    // Cập nhật vị trí camera để theo dõi cá
    camera.x = static_cast<int>(fishX - SCREEN_WIDTH / 2);
    camera.y = static_cast<int>(fishY - SCREEN_HEIGHT / 2);


    // Camera không vượt quá biên
    if (camera.x < 0) {
        camera.x = 0;   
    }
    if (camera.x + camera.w > BACKGROUND_WIDTH) {
        camera.x = BACKGROUND_WIDTH - camera.w;
    }

    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.y + camera.h > BACKGROUND_HEIGHT) {
        camera.y = BACKGROUND_HEIGHT - camera.h;
    }
}

















