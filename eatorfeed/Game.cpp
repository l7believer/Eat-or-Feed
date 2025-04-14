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

    for (int i = 0; i < 3; ++i) {
        Kethu12 enemy;
        enemy.loadSpriteSheet("res/Kethu12_left.png", "res/Kethu12_right.png", renderer);
        enemies12.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu11 enemy;
        enemy.loadSpriteSheet("res/Kethu11_left.png", "res/Kethu11_right.png", renderer);
        enemies11.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu10 enemy;
        enemy.loadSpriteSheet("res/Kethu10_left.png", "res/Kethu10_right.png", renderer);
        enemies10.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu9 enemy;
        enemy.loadSpriteSheet("res/Kethu9_left.png", "res/Kethu9_right.png", renderer);
        enemies9.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu8 enemy;
        enemy.loadSpriteSheet("res/Kethu8_left.png", "res/Kethu8_right.png", renderer);
        enemies8.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu7 enemy;
        enemy.loadSpriteSheet("res/Kethu7_left.png", "res/Kethu7_right.png", renderer);
        enemies7.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu6 enemy;
        enemy.loadSpriteSheet("res/Kethu6_left.png", "res/Kethu6_right.png", renderer);
        enemies6.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu5 enemy;
        enemy.loadSpriteSheet("res/Kethu5_left.png", "res/Kethu5_right.png", renderer);
        enemies5.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu4 enemy;
        enemy.loadSpriteSheet("res/Kethu4_left.png", "res/Kethu4_right.png", renderer);
        enemies4.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu3 enemy;
        enemy.loadSpriteSheet("res/Kethu3_left.png", "res/Kethu3_right.png", renderer);
        enemies3.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu2 enemy;
        enemy.loadSpriteSheet("res/Kethu2_left.png", "res/Kethu2_right.png", renderer);
        enemies2.push_back(enemy);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu1 enemy;
        enemy.loadSpriteSheet("res/Kethu1_left.png", "res/Kethu1_right.png", renderer);
        enemies1.push_back(enemy);
    }
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

    SDL_Rect fishBox = fish.getCollisionBox();

    for (auto& enemy : enemies12) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            resetGame();
        }
    }
    for (auto& enemy : enemies11) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            enemy.reset();
        }
    }
    for (auto& enemy : enemies10) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            resetGame();
        }
    }
    for (auto& enemy : enemies9) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            resetGame();
        }
    }
    for (auto& enemy : enemies8) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            resetGame();
        }
    }
    for (auto& enemy : enemies7) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            enemy.reset();
        }
    }
    for (auto& enemy : enemies6) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            enemy.reset();
        }
    }
    for (auto& enemy : enemies5) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            resetGame();
        }
    }
    for (auto& enemy : enemies4) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            resetGame();
        }
    }
    for (auto& enemy : enemies3) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            resetGame();
        }
    }
    for (auto& enemy : enemies2) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            resetGame();
        }
    }
    for (auto& enemy : enemies1) {
        enemy.updatePosition();
        SDL_Rect enemyBox = enemy.getCollisionBox();
        if (SDL_HasIntersection(&fishBox, &enemyBox)) {
            enemy.reset();
        }
    }

    fish.updatePosition(mouseX, mouseY);
}

void Game::render() {
    SDL_RenderClear(renderer);

    // Vẽ background theo camera
    SDL_RenderCopy(renderer, backgroundTexture, &camera, nullptr);

    for (auto& enemy : enemies12) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies11) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies10) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies9) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies8) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies7) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies6) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies5) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies4) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies3) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies2) {
        enemy.render(renderer, camera);
    }
    for (auto& enemy : enemies1) {
        enemy.render(renderer, camera);
    }
    
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

void Game::resetGame() {
    // Reset vị trí cá chính về giữa màn
    fish = Fish(); // nếu Fish có constructor mặc định
    fish.loadSpriteSheet("res/player_left.png", "res/player_right.png", renderer);

    // Reset camera
    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    // Reset các enemy
    enemies1.clear();
    enemies2.clear();
    enemies3.clear();
    enemies4.clear();
    enemies5.clear();
    enemies6.clear();
    enemies7.clear();
    enemies8.clear();
    enemies9.clear();
    enemies10.clear();
    enemies11.clear();
    enemies12.clear();

    for (int i = 0; i < 3; ++i) {
        Kethu1 e;
        e.loadSpriteSheet("res/Kethu1_left.png", "res/Kethu1_right.png", renderer);
        enemies1.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu2 e;
        e.loadSpriteSheet("res/Kethu2_left.png", "res/Kethu2_right.png", renderer);
        enemies2.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu3 e;
        e.loadSpriteSheet("res/Kethu3_left.png", "res/Kethu3_right.png", renderer);
        enemies3.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu4 e;
        e.loadSpriteSheet("res/Kethu4_left.png", "res/Kethu4_right.png", renderer);
        enemies4.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu5 e;
        e.loadSpriteSheet("res/Kethu5_left.png", "res/Kethu5_right.png", renderer);
        enemies5.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu6 e;
        e.loadSpriteSheet("res/Kethu6_left.png", "res/Kethu6_right.png", renderer);
        enemies6.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu7 e;
        e.loadSpriteSheet("res/Kethu7_left.png", "res/Kethu7_right.png", renderer);
        enemies7.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu8 e;
        e.loadSpriteSheet("res/Kethu8_left.png", "res/Kethu8_right.png", renderer);
        enemies8.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu9 e;
        e.loadSpriteSheet("res/Kethu9_left.png", "res/Kethu9_right.png", renderer);
        enemies9.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu10 e;
        e.loadSpriteSheet("res/Kethu10_left.png", "res/Kethu10_right.png", renderer);
        enemies10.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu11 e;
        e.loadSpriteSheet("res/Kethu11_left.png", "res/Kethu11_right.png", renderer);
        enemies11.push_back(e);
    }
    for (int i = 0; i < 3; ++i) {
        Kethu12 e;
        e.loadSpriteSheet("res/Kethu12_left.png", "res/Kethu12_right.png", renderer);
        enemies12.push_back(e);
    }
}













