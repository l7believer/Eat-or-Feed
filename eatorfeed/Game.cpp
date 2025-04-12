#include "Game.h"
#include <SDL_image.h>
#include "Constants.h"

Game::Game() : window(nullptr), renderer(nullptr), backgroundTexture(nullptr), quit(false) {}

Game::~Game() {
    close();
}

//bool Game::init() {
//    SDL_Init(SDL_INIT_VIDEO);
//    IMG_Init(IMG_INIT_PNG);
//
//    window = SDL_CreateWindow("Fish Game",
//        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//        SCREEN_WIDTH, SCREEN_HEIGHT,
//        SDL_WINDOW_FULLSCREEN); // Toàn màn hình
//
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//
//    SDL_ShowCursor(SDL_DISABLE); // Ẩn chuột
//
//    SDL_Surface* bg = IMG_Load("res/eq.png");
//    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bg);
//    SDL_FreeSurface(bg);
//
//    fish.loadSpriteSheet("res/player_left.png", "res/player_right.png", renderer);
//
//    return true;
//}
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

    fish.loadSpriteSheet("res/player_left.png", "res/player_right.png", renderer);

    return true;
}



void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) quit = true;
    }

    // Luôn lấy tọa độ chuột mỗi frame
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Chuyển đổi tọa độ chuột sang hệ tọa độ của background
    mouseX += camera.x;
    mouseY += camera.y;

    fish.updatePosition(mouseX, mouseY);
}


//void Game::render() {
//    SDL_RenderClear(renderer);
//
//    SDL_Rect bgDestRect = { 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT };
//    SDL_RenderCopy(renderer, backgroundTexture, nullptr, &bgDestRect); // Vẽ full background
//    fish.render(renderer); // Vẽ cá
//
//    SDL_RenderPresent(renderer);
//}
//void Game::render() {
//    SDL_RenderClear(renderer);
//
//    // Tính toán vị trí để căn giữa background
//    int bgX = (SCREEN_WIDTH - BACKGROUND_WIDTH) / 2;
//    int bgY = (SCREEN_HEIGHT - BACKGROUND_HEIGHT) / 2;
//
//    SDL_Rect bgDestRect = { bgX, bgY, BACKGROUND_WIDTH, BACKGROUND_HEIGHT };
//
//    // Vẽ background ở giữa màn hình
//    SDL_RenderCopy(renderer, backgroundTexture, nullptr, &bgDestRect);
//
//    // Vẽ cá
//    fish.render(renderer);
//
//    SDL_RenderPresent(renderer);
//}
void Game::render() {
    SDL_RenderClear(renderer);

    // Vẽ background theo camera
    SDL_RenderCopy(renderer, backgroundTexture, &camera, nullptr);

    // Vẽ cá
    fish.render(renderer, camera);

    SDL_RenderPresent(renderer);
}


//void Game::run() {
//    while (!quit) {
//        handleEvents();
//        render();
//        SDL_Delay(5); // FPS
//    }
//}
void Game::run() {
    while (!quit) {
        handleEvents();
        updateCamera(); // Cập nhật camera
        render();
        SDL_Delay(16); // ~60 FPS
    }
}



void Game::close() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

/// 
/// 
/// 
//void Game::updateCamera() {
//    // Lấy vị trí của cá
//    float fishX = fish.getX();
//    float fishY = fish.getY();
//
//    // Cập nhật vị trí camera để theo dõi cá
//    camera.x = static_cast<int>(fishX - SCREEN_WIDTH / 2);
//    camera.y = static_cast<int>(fishY - SCREEN_HEIGHT / 2);
//
//    // Đảm bảo camera không vượt ra ngoài biên của background
//    if (camera.x < 0) camera.x = 0;
//    if (camera.y < 0) camera.y = 0;
//    if (camera.x + camera.w > BACKGROUND_WIDTH ) camera.x = BACKGROUND_WIDTH  - camera.w;
//    if (camera.y + camera.h > BACKGROUND_HEIGHT ) camera.y = BACKGROUND_HEIGHT  - camera.h;
//}
void Game::updateCamera() {
    // Lấy vị trí của cá
    float fishX = fish.getX();
    float fishY = fish.getY();

    // Cập nhật vị trí camera để theo dõi cá
    camera.x = static_cast<int>(fishX - SCREEN_WIDTH / 2);
    camera.y = static_cast<int>(fishY - SCREEN_HEIGHT / 2);


    // Đảm bảo camera không vượt ra ngoài biên của background
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















