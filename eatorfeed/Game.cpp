#include "Game.h"
#include <SDL_image.h>
#include "Constants.h"
#include <SDL_ttf.h>

Game::Game() : window(nullptr), renderer(nullptr), backgroundTexture(nullptr), quit(false), isPaused(false), score(0) {}

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

    SDL_ShowCursor(SDL_ENABLE);

    SDL_Surface* menuSurface = IMG_Load("res/Menu.png");
    menuTexture = SDL_CreateTextureFromSurface(renderer, menuSurface);
    SDL_FreeSurface(menuSurface);

    inMenu = true;

    SDL_Surface* bg = IMG_Load("res/eq.png");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);

    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_Surface* pauseSurface = IMG_Load("res/Pause.png");
    pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);
    SDL_FreeSurface(pauseSurface);

    SDL_Surface* youWinSurface = IMG_Load("res/Youwin.png");
    youWinTexture = SDL_CreateTextureFromSurface(renderer, youWinSurface);
    SDL_FreeSurface(youWinSurface);

    SDL_Surface* youLoseSurface = IMG_Load("res/Youlose.png");
    youLoseTexture = SDL_CreateTextureFromSurface(renderer, youLoseSurface);
    SDL_FreeSurface(youLoseSurface);

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

    if (TTF_Init() == -1)
        return false;

    font = TTF_OpenFont("res/COOPBL.TTF", 36);
    if (!font)
        return false;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
        return false;
    }
    boostSound = Mix_LoadWAV("res/Boost.wav");
    eatSound = Mix_LoadWAV("res/Eat.wav");
    menuSound = Mix_LoadWAV("res/Menu.mp3");
    playingSound = Mix_LoadWAV("res/Playing.mp3");
    sizeupSound = Mix_LoadWAV("res/Sizeup.wav");
    youwinSound = Mix_LoadWAV("res/Youwin.wav");
    youloseSound = Mix_LoadWAV("res/Youlose.wav");

    return true;
}


void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) quit = true;

        if (gameState == PLAYING && !inMenu && !isPaused && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            fish.startBoost();
            Mix_PlayChannel(2, boostSound, 0);
        }

        if (inMenu && e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;

            if (mouseX >= 679 && mouseX <= 1212 && mouseY >= 525 && mouseY <= 686) {
                inMenu = false;
                SDL_ShowCursor(SDL_DISABLE);
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

        if (gameState == WIN && e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;

            if (mouseX >= 726 && mouseX <= 1200 && mouseY >= 591 && mouseY <= 700) {
                resetGame();
                gameState = PLAYING;
            }

            if (mouseX >= 726 && mouseX <= 1200 && mouseY >= 725 && mouseY <= 833) {
                quit = true;
            }
        }

        if (gameState == LOSE && e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;

            if (mouseX >= 726 && mouseX <= 1200 && mouseY >= 585 && mouseY <= 700) {
                resetGame();
                gameState = PLAYING;
            }

            if (mouseX >= 726 && mouseX <= 1200 && mouseY >= 721 && mouseY <= 826) {
                quit = true;
            }
        }

        fish.updateBoost(); // Cập nhật trạng thái tăng tốc
    }

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Chuyển đổi tọa độ chuột sang hệ tọa độ của background
    mouseX += camera.x;
    mouseY += camera.y;

    SDL_Rect fishBox = fish.getCollisionBox();

    if (!inMenu && !isPaused && gameState == PLAYING) {
        for (auto& enemy : enemies12) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                if (score >= 300) {
                    score += 30;
                    fish.isEating = true;
                    fish.eatFrame = 0;
                    fish.eatFrameTime = 0;
                    enemy.reset();
                    Mix_PlayChannel(2, eatSound, 0);
                }
                else {
                    enemy.isEating = true;
                    enemy.eatFrame = 0;
                    enemy.eatFrameTime = 0;
                    if (gameState != LOSE) Mix_PlayChannel(3, youloseSound, 0);
                    gameState = LOSE;
                    loseStartTime = SDL_GetTicks();
                    Mix_PlayChannel(2, eatSound, 0);
                }
            }
        }
        for (auto& enemy : enemies11) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                score += 10;
                fish.isEating = true;
                fish.eatFrame = 0;
                fish.eatFrameTime = 0;
                enemy.reset();
                Mix_PlayChannel(2, eatSound, 0);
            }
        }
        for (auto& enemy : enemies10) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                if (score >= 500) {
                    score += 100;
                    fish.isEating = true;
                    fish.eatFrame = 0;
                    fish.eatFrameTime = 0;
                    enemy.reset();
                    Mix_PlayChannel(2, eatSound, 0);
                }
                else {
                    enemy.isEating = true;
                    enemy.eatFrame = 0;
                    enemy.eatFrameTime = 0;
                    if (gameState != LOSE) Mix_PlayChannel(3, youloseSound, 0);
                    gameState = LOSE;
                    loseStartTime = SDL_GetTicks();
                    Mix_PlayChannel(2, eatSound, 0);
                }
            }
        }
        for (auto& enemy : enemies9) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                if (score >= 300) {
                    score += 30;
                    fish.isEating = true;
                    fish.eatFrame = 0;
                    fish.eatFrameTime = 0;
                    enemy.reset();
                    Mix_PlayChannel(2, eatSound, 0);
                }
                else {
                    enemy.isEating = true;
                    enemy.eatFrame = 0;
                    enemy.eatFrameTime = 0;
                    if (gameState != LOSE) Mix_PlayChannel(3, youloseSound, 0);
                    gameState = LOSE;
                    loseStartTime = SDL_GetTicks();
                    Mix_PlayChannel(2, eatSound, 0);
                }
            }
        }
        for (auto& enemy : enemies8) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                if (score >= 200) {
                    score += 25;
                    fish.isEating = true;
                    fish.eatFrame = 0;
                    fish.eatFrameTime = 0;
                    enemy.reset();
                    Mix_PlayChannel(2, eatSound, 0);
                }
                else {
                    enemy.isEating = true;
                    enemy.eatFrame = 0;
                    enemy.eatFrameTime = 0;
                    if (gameState != LOSE) Mix_PlayChannel(4, youloseSound, 0);
                    gameState = LOSE;
                    loseStartTime = SDL_GetTicks();
                    Mix_PlayChannel(2, eatSound, 0);
                }
            }
        }
        for (auto& enemy : enemies7) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                score += 5;
                fish.isEating = true;
                fish.eatFrame = 0;
                fish.eatFrameTime = 0;
                enemy.reset();
                Mix_PlayChannel(2, eatSound, 0);
            }
        }
        for (auto& enemy : enemies6) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                score += 15;
                fish.isEating = true;
                fish.eatFrame = 0;
                fish.eatFrameTime = 0;
                enemy.reset();
                Mix_PlayChannel(2, eatSound, 0);
            }
        }
        for (auto& enemy : enemies5) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                if (score >= 100) {
                    score += 20;
                    fish.isEating = true;
                    fish.eatFrame = 0;
                    fish.eatFrameTime = 0;
                    enemy.reset();
                    Mix_PlayChannel(2, eatSound, 0);
                }
                else {
                    enemy.isEating = true;
                    enemy.eatFrame = 0;
                    enemy.eatFrameTime = 0;
                    if (gameState != LOSE) Mix_PlayChannel(3, youloseSound, 0);
                    gameState = LOSE;
                    loseStartTime = SDL_GetTicks();
                    Mix_PlayChannel(2, eatSound, 0);
                }
            }
        }
        for (auto& enemy : enemies4) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                if (score >= 100) {
                    score += 20;
                    fish.isEating = true;
                    fish.eatFrame = 0;
                    fish.eatFrameTime = 0;
                    enemy.reset();
                    Mix_PlayChannel(2, eatSound, 0);
                }
                else {
                    enemy.isEating = true;
                    enemy.eatFrame = 0;
                    enemy.eatFrameTime = 0;
                    if (gameState != LOSE) Mix_PlayChannel(3, youloseSound, 0);
                    gameState = LOSE;
                    loseStartTime = SDL_GetTicks();
                    Mix_PlayChannel(2, eatSound, 0);
                }
            }
        }
        for (auto& enemy : enemies3) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                if (score >= 200) {
                    score += 25;
                    fish.isEating = true;
                    fish.eatFrame = 0;
                    fish.eatFrameTime = 0;
                    enemy.reset();
                    Mix_PlayChannel(2, eatSound, 0);
                }
                else {
                    enemy.isEating = true;
                    enemy.eatFrame = 0;
                    enemy.eatFrameTime = 0;
                    if (gameState != LOSE) Mix_PlayChannel(3, youloseSound, 0);
                    gameState = LOSE;
                    loseStartTime = SDL_GetTicks();
                    Mix_PlayChannel(2, eatSound, 0);
                }
            }
        }
        for (auto& enemy : enemies2) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                if (score >= 300) {
                    score += 30;
                    fish.isEating = true;
                    fish.eatFrame = 0;
                    fish.eatFrameTime = 0;
                    enemy.reset();
                    Mix_PlayChannel(2, eatSound, 0);
                }
                else {
                    enemy.isEating = true;
                    enemy.eatFrame = 0;
                    enemy.eatFrameTime = 0;
                    if (gameState != LOSE) Mix_PlayChannel(3, youloseSound, 0);
                    gameState = LOSE;
                    loseStartTime = SDL_GetTicks();
                    Mix_PlayChannel(2, eatSound, 0);
                }
            }
        }
        for (auto& enemy : enemies1) {
            enemy.updatePosition();
            SDL_Rect enemyBox = enemy.getCollisionBox();
            if (SDL_HasIntersection(&fishBox, &enemyBox)) {
                score += 10;
                fish.isEating = true;
                fish.eatFrame = 0;
                fish.eatFrameTime = 0;
                enemy.reset();
                Mix_PlayChannel(2, eatSound, 0);
            }
        }
        fish.updatePosition(mouseX, mouseY);
        if (score >= 1000) {
            if (gameState != WIN) Mix_PlayChannel(2, youwinSound, 0);
            gameState = WIN;
            winStartTime = SDL_GetTicks();
        }
    }

    if (score >= 100 && score < 200) {
        if (fish.scale != 1.1f) Mix_PlayChannel(2, sizeupSound, 0);
        fish.setScale(1.1f); // Tăng kích thước cá lên 1.1 lần
    }
    else if (score >= 200 && score < 300) {
        if (fish.scale != 1.2f) Mix_PlayChannel(2, sizeupSound, 0);
        fish.setScale(1.2f); // Tăng kích thước cá lên 1.2 lần
    }
    else if (score >= 300 && score < 500) {
        if (fish.scale != 1.4f) Mix_PlayChannel(2, sizeupSound, 0);
        fish.setScale(1.4f); // Tăng kích thước cá lên 1.4 lần
    }
    else if (score >= 500) {
        if (fish.scale != 2.0f) Mix_PlayChannel(2, sizeupSound, 0);
        fish.setScale(2.0f); // Tăng kích thước cá lên gấp 2 lần
    }
}

void Game::render() {

    if (!inMenu && Mix_Playing(0)) {
        Mix_HaltChannel(0); 
    }

    if (gameState == PLAYING && !Mix_Playing(1)) {
        Mix_PlayChannel(1, playingSound, -1); 
    }

    if (gameState != PLAYING && Mix_Playing(1)) {
        Mix_HaltChannel(1);
    }

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

    if (gameState != LOSE) {
        fish.render(renderer, camera);
    }

    if (isPaused) {
        renderPause();
    }

    if (gameState == WIN) {
        if (SDL_GetTicks() - winStartTime >= 1000) {
            SDL_ShowCursor(SDL_ENABLE);
            renderYouWin();
        }
    }

    if (gameState == LOSE) {
        if (SDL_GetTicks() - loseStartTime >= 1000) {
            SDL_ShowCursor(SDL_ENABLE);
            renderYouLose();
        }
    }

    std::string scoreText = "Your score: " + std::to_string(score);

    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);

    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect textRect = { 20, 20, textSurface->w, textSurface->h };

        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    // In hình những cá ăn được
    int x = SCREEN_WIDTH - 20;
    int y = 20;
    int spacing = 10;

    // Kethu7.png (giảm kích thước còn 1/4 so với ban đầu)
    SDL_Texture* kethu7Texture = IMG_LoadTexture(renderer, "res/Kethu7.png");
    SDL_Rect kethu7Rect = { x - (65 / 2), y, 65 / 2, 47 / 2 };
    SDL_RenderCopy(renderer, kethu7Texture, nullptr, &kethu7Rect);
    x -= kethu7Rect.w + spacing;

    // Kethu1.png
    SDL_Texture* kethu1Texture = IMG_LoadTexture(renderer, "res/Kethu1.png");
    SDL_Rect kethu1Rect = { x - (125 / 2), y, 125 / 2, 105 / 2 };
    SDL_RenderCopy(renderer, kethu1Texture, nullptr, &kethu1Rect);
    x -= kethu1Rect.w + spacing;

    // Kethu11.png
    SDL_Texture* kethu11Texture = IMG_LoadTexture(renderer, "res/Kethu11.png");
    SDL_Rect kethu11Rect = { x - (166 / 2), y, 166 / 2, 102 / 2 };
    SDL_RenderCopy(renderer, kethu11Texture, nullptr, &kethu11Rect);
    x -= kethu11Rect.w + spacing;

    // Kethu6.png
    SDL_Texture* kethu6Texture = IMG_LoadTexture(renderer, "res/Kethu6.png");
    SDL_Rect kethu6Rect = { x - (247 / 2), y, 247 / 2, 171 / 2 };
    SDL_RenderCopy(renderer, kethu6Texture, nullptr, &kethu6Rect);
    x -= kethu6Rect.w + spacing;

    // Hiển thị thêm khi score >= 100
    if (score >= 100) {
        SDL_Texture* kethu4Texture = IMG_LoadTexture(renderer, "res/Kethu4.png");
        SDL_Rect kethu4Rect = { x - (179 / 2), y, 179 / 2, 178 / 2 };
        SDL_RenderCopy(renderer, kethu4Texture, nullptr, &kethu4Rect);
        x -= kethu4Rect.w + spacing;

        SDL_Texture* kethu5Texture = IMG_LoadTexture(renderer, "res/Kethu5.png");
        SDL_Rect kethu5Rect = { x - (175 / 2), y, 175 / 2, 156 / 2 };
        SDL_RenderCopy(renderer, kethu5Texture, nullptr, &kethu5Rect);
        x -= kethu5Rect.w + spacing;
    }

    // Hiển thị thêm khi score >= 200
    if (score >= 200) {
        SDL_Texture* kethu8Texture = IMG_LoadTexture(renderer, "res/Kethu8.png");
        SDL_Rect kethu8Rect = { x - (199 / 2), y, 199 / 2, 144 / 2 };
        SDL_RenderCopy(renderer, kethu8Texture, nullptr, &kethu8Rect);
        x -= kethu8Rect.w + spacing;

        SDL_Texture* kethu3Texture = IMG_LoadTexture(renderer, "res/Kethu3.png");
        SDL_Rect kethu3Rect = { x - (268 / 2), y, 268 / 2, 119 / 2 };
        SDL_RenderCopy(renderer, kethu3Texture, nullptr, &kethu3Rect);
        x -= kethu3Rect.w + spacing;
    }

    // Hiển thị thêm khi score >= 300
    if (score >= 300) {
        SDL_Texture* kethu9Texture = IMG_LoadTexture(renderer, "res/Kethu9.png");
        SDL_Rect kethu9Rect = { x - (188 / 2), y, 188 / 2, 119 / 2 };
        SDL_RenderCopy(renderer, kethu9Texture, nullptr, &kethu9Rect);
        x -= kethu9Rect.w + spacing;

        SDL_Texture* kethu2Texture = IMG_LoadTexture(renderer, "res/Kethu2.png");
        SDL_Rect kethu2Rect = { x - (199 / 2), y, 199 / 2, 178 / 2 };
        SDL_RenderCopy(renderer, kethu2Texture, nullptr, &kethu2Rect);
        x -= kethu2Rect.w + spacing;

        SDL_Texture* kethu12Texture = IMG_LoadTexture(renderer, "res/Kethu12.png");
        SDL_Rect kethu12Rect = { x - (238 / 2), y, 238 / 2, 117 / 2 };
        SDL_RenderCopy(renderer, kethu12Texture, nullptr, &kethu12Rect);
        x -= kethu12Rect.w + spacing;
    }

    // Hiển thị thêm khi score >= 500
    if (score >= 500) {
        SDL_Texture* kethu10Texture = IMG_LoadTexture(renderer, "res/Kethu10.png");
        SDL_Rect kethu10Rect = { x - (370 / 4), y, 370 / 4, 139 / 4 }; // Thu nhỏ còn 1/4
        SDL_RenderCopy(renderer, kethu10Texture, nullptr, &kethu10Rect);
        x -= kethu10Rect.w + spacing;
    }

    SDL_RenderPresent(renderer);

}

void Game::run() {
    while (!quit) {
        handleEvents();
        if (!isPaused && gameState == PLAYING) {
            updateCamera();
        }
        render();
        SDL_Delay(16); //FPS
    }
}


void Game::close() {
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(youWinTexture);
    SDL_DestroyTexture(youLoseTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(pauseTexture);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    TTF_CloseFont(font);
    TTF_Quit();

    Mix_FreeChunk(boostSound);
    Mix_FreeChunk(eatSound);
    Mix_FreeChunk(menuSound);
    Mix_FreeChunk(playingSound);
    Mix_FreeChunk(sizeupSound);
    Mix_FreeChunk(youwinSound);
    Mix_FreeChunk(youloseSound);

    boostSound = nullptr;
    eatSound = nullptr;
    menuSound = nullptr;
    playingSound = nullptr;
    sizeupSound = nullptr;
    youwinSound = nullptr;
    youloseSound = nullptr;

    Mix_CloseAudio();
}


void Game::updateCamera() {
    float fishX = fish.getX();
    float fishY = fish.getY();

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
    fish = Fish();
    fish.loadSpriteSheet("res/player_left.png", "res/player_right.png", renderer);

    SDL_ShowCursor(SDL_DISABLE);
    // Reset camera
    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    score = 0;

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

    gameState = PLAYING;
}

void Game::renderMenu() {

    Mix_PlayChannel(0, menuSound, -1);

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, menuTexture, nullptr, nullptr);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Rect playRect = { 679, 525, 1212 - 679, 686 - 525 };

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
        SDL_Rect underlineExit = { 737, 820, 1212 - (737 - 679) - 737, 5 };
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

void Game::renderYouWin() {
    Mix_PlayChannel(-1, youwinSound, 0);
    int winWidth = 1920;
    int winHeight = 1200;
    SDL_Rect winRect = {
        (SCREEN_WIDTH - winWidth) / 2,
        (SCREEN_HEIGHT - winHeight) / 2,
        winWidth,
        winHeight
    };
    SDL_RenderCopy(renderer, youWinTexture, nullptr, &winRect);

    TTF_Font* largeFont = TTF_OpenFont("res/arial.ttf", 72);
    if (!largeFont) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    // Hiển thị điểm số
    std::string scoreText = std::to_string(score);
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(largeFont, scoreText.c_str(), textColor);

    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect textRect = { 1055, 480, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    TTF_CloseFont(largeFont);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Rect replayRect = { 726, 591, 1200 - 726, 700 - 591 };
    if (mouseX >= replayRect.x && mouseX <= replayRect.x + replayRect.w &&
        mouseY >= replayRect.y && mouseY <= replayRect.y + replayRect.h) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect underlineReplay = { 856, 675, 1056 - 856, 5 };
        SDL_RenderFillRect(renderer, &underlineReplay);
    }

    SDL_Rect quitRect = { 726, 725, 1200 - 726, 833 - 725 };
    if (mouseX >= quitRect.x && mouseX <= quitRect.x + quitRect.w &&
        mouseY >= quitRect.y && mouseY <= quitRect.y + quitRect.h) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect underlineQuit = { 896, 807, 1027 - 896, 5 };
        SDL_RenderFillRect(renderer, &underlineQuit);
    }
}

void Game::renderYouLose() {
    int loseWidth = 1920;
    int loseHeight = 1200;
    SDL_Rect loseRect = {
        (SCREEN_WIDTH - loseWidth) / 2,
        (SCREEN_HEIGHT - loseHeight) / 2,
        loseWidth,
        loseHeight
    };
    SDL_RenderCopy(renderer, youLoseTexture, nullptr, &loseRect);

    TTF_Font* largeFont = TTF_OpenFont("res/arial.ttf", 72);
    if (!largeFont) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    std::string scoreText = std::to_string(score);
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(largeFont, scoreText.c_str(), textColor);

    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect textRect = { 1075, 475, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    TTF_CloseFont(largeFont);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Rect replayRect = { 726, 585, 1200 - 726, 700 - 585 };
    if (mouseX >= replayRect.x && mouseX <= replayRect.x + replayRect.w &&
        mouseY >= replayRect.y && mouseY <= replayRect.y + replayRect.h) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect underlineReplay = { 856, 670, 1066 - 856, 5 };
        SDL_RenderFillRect(renderer, &underlineReplay);
    }

    SDL_Rect quitRect = { 726, 721, 1200 - 726, 826 - 721 };
    if (mouseX >= quitRect.x && mouseX <= quitRect.x + quitRect.w &&
        mouseY >= quitRect.y && mouseY <= quitRect.y + quitRect.h) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect underlineQuit = { 895, 806, 1027 - 895, 5 };
        SDL_RenderFillRect(renderer, &underlineQuit);
    }
}
















