#include "Game.h"
#include <SDL_image.h>
#include "Constants.h"


Game::Game() : window(nullptr), renderer(nullptr), backgroundTexture(nullptr), quit(false), isPaused(false) {}

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

    SDL_ShowCursor(SDL_ENABLE); // Hiển thị chuột khi vào menu

    SDL_Surface* menuSurface = IMG_Load("res/Menu.png");
    menuTexture = SDL_CreateTextureFromSurface(renderer, menuSurface);
    SDL_FreeSurface(menuSurface);

    inMenu = true; // Bắt đầu ở menu

    SDL_Surface* bg = IMG_Load("res/eq.png");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);

    // Khởi tạo camera
    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_Surface* pauseSurface = IMG_Load("res/Pause.png");
    pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);
    SDL_FreeSurface(pauseSurface);

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

        if (inMenu && e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;

            if (mouseX >= 679 && mouseX <= 1212 && mouseY >= 525 && mouseY <= 686) {
                inMenu = false;
                SDL_ShowCursor(SDL_DISABLE); // Ẩn chuột
            }

            if (mouseX >= 679 && mouseX <= 1212 && mouseY >= 717 && mouseY <= 855) {
                quit = true;
            }
        }
        if (isPaused && e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;

            if (mouseX >= 725 && mouseX <= 1200 && mouseY >= 412 && mouseY <= 523) {
				isPaused = false;
                SDL_ShowCursor(SDL_DISABLE);
            }
            
            if (mouseX >= 725 && mouseX <= 1200 && mouseY >= 565 && mouseY <= 680) {
                resetGame();
				isPaused = false;
            }

			if (mouseX >= 725 && mouseX <= 1200 && mouseY >= 722 && mouseY <= 835) {
				quit = true;
			}
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p) {
            isPaused = !isPaused;
            if (isPaused) {
                SDL_ShowCursor(SDL_ENABLE);
            }
            else {
                SDL_ShowCursor(SDL_DISABLE);
            }
        }
    }

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Chuyển đổi tọa độ chuột sang hệ tọa độ của background
    mouseX += camera.x;
    mouseY += camera.y;

    SDL_Rect fishBox = fish.getCollisionBox();

    if (!isPaused) {
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
                fish.isEating = true;
                fish.eatFrame = 0;
                fish.eatFrameTime = 0;
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
                fish.isEating = true;
                fish.eatFrame = 0;
                fish.eatFrameTime = 0;
                enemy.reset();
            }
        }
        for (auto& enemy : enemies6) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                fish.isEating = true;
                fish.eatFrame = 0;
                fish.eatFrameTime = 0;
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
                fish.isEating = true;
                fish.eatFrame = 0;
                fish.eatFrameTime = 0;
                enemy.reset();
            }
        }
        fish.updatePosition(mouseX, mouseY);
    }
}

void Game::render() {
    if (inMenu) {
        renderMenu();
        return;
    }

    SDL_RenderClear(renderer);

    // Vẽ background theo camera
    SDL_RenderCopy(renderer, backgroundTexture, &camera, nullptr);

    for (auto& enemy : enemies12) enemy.render(renderer, camera);
    for (auto& enemy : enemies11) enemy.render(renderer, camera);
    for (auto& enemy : enemies10) enemy.render(renderer, camera);
    for (auto& enemy : enemies9) enemy.render(renderer, camera);
    for (auto& enemy : enemies8) enemy.render(renderer, camera);
    for (auto& enemy : enemies7) enemy.render(renderer, camera);
    for (auto& enemy : enemies6) enemy.render(renderer, camera);
    for (auto& enemy : enemies5) enemy.render(renderer, camera);
    for (auto& enemy : enemies4) enemy.render(renderer, camera);
    for (auto& enemy : enemies3) enemy.render(renderer, camera);
    for (auto& enemy : enemies2) enemy.render(renderer, camera);
    for (auto& enemy : enemies1) enemy.render(renderer, camera);

    fish.render(renderer, camera);

    if (isPaused) {
        renderPause();
    }

    SDL_RenderPresent(renderer);
}

void Game::run() {
    while (!quit) {
        handleEvents();
        if (!isPaused) {
            updateCamera();
        }
        render();
        SDL_Delay(16); //FPS
    }
}


void Game::close() {
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(pauseTexture);
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

void Game::renderMenu() {
    SDL_RenderClear(renderer);

    // Vẽ menu nền
    SDL_RenderCopy(renderer, menuTexture, nullptr, nullptr);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Vùng "PLAY"
    SDL_Rect playRect = { 679, 525, 1212 - 679, 686 - 525 };
    // Vùng "EXIT GAME"
    SDL_Rect exitRect = { 679, 717, 1212 - 679, 855 - 717 };

    if (mouseX >= playRect.x && mouseX <= playRect.x + playRect.w &&
        mouseY >= playRect.y && mouseY <= playRect.y + playRect.h) {
        SDL_SetRenderDrawColor(renderer, 37, 150, 190, 190);
        SDL_Rect underlinePlay = { 787, 655, 1212 - (787 - 679) - 787, 5 };
        SDL_RenderFillRect(renderer, &underlinePlay);
    }

    if (mouseX >= exitRect.x && mouseX <= exitRect.x + exitRect.w &&
        mouseY >= exitRect.y && mouseY <= exitRect.y + exitRect.h) {
        SDL_SetRenderDrawColor(renderer, 37, 150, 190, 190);
        SDL_Rect underlineExit = { 737, 820, 1212 - (737-679) - 737, 5 };
        SDL_RenderFillRect(renderer, &underlineExit);
    }

    SDL_RenderPresent(renderer);
}

void Game::renderPause() {
    int pauseWidth = 1024;
    int pauseHeight = 1536;
    SDL_Rect pauseRect = {
        (SCREEN_WIDTH - pauseWidth) / 2,
        (SCREEN_HEIGHT - pauseHeight) / 2,
        pauseWidth,
        pauseHeight
    };
    SDL_RenderCopy(renderer, pauseTexture, nullptr, &pauseRect);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Rect resumeRect = { 725, 412, 1200 - 725, 523 - 412 };

    if (mouseX >= resumeRect.x && mouseX <= resumeRect.x + resumeRect.w &&
        mouseY >= resumeRect.y && mouseY <= resumeRect.y + resumeRect.h) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect underlinePlay = { 768, 503, 1200 - (765 - 725) - 765 - 15, 5 };
        SDL_RenderFillRect(renderer, &underlinePlay);
    }
    SDL_Rect replayRect = { 725, 565, 1200 - 725, 680 - 565 };

    if (mouseX >= replayRect.x && mouseX <= replayRect.x + replayRect.w &&
        mouseY >= replayRect.y && mouseY <= replayRect.y + replayRect.h) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect underlinePlay = { 864, 659, 1200 - (864 - 725) - 864 - 10, 5 };
        SDL_RenderFillRect(renderer, &underlinePlay);
    }
    SDL_Rect quitRect = { 725, 722, 1200 - 725, 835 - 722 };

    if (mouseX >= quitRect.x && mouseX <= quitRect.x + quitRect.w &&
        mouseY >= quitRect.y && mouseY <= quitRect.y + quitRect.h) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect underlinePlay = { 898, 811, 1200 - (898 - 725) - 898, 5 };
        SDL_RenderFillRect(renderer, &underlinePlay);
    }
}















