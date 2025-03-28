#include "Enemy.h"
#include <SDL_image.h>

Enemy::Enemy() : leftSpriteSheet(nullptr), rightSpriteSheet(nullptr), frameWidth(0), frameHeight(0), currentFrame(0), frameDirection(1), lastFrameTime(0), state(EnemyState::IDLE), dir(EnemyDirection::RIGHT), posX(0), posY(0) {}

Enemy::~Enemy() {
    freeSpriteSheet();
}

bool Enemy::loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer) {
    freeSpriteSheet();
    SDL_Surface* loadedSurface = IMG_Load(leftPath.c_str());
    if (loadedSurface == nullptr) {
        return false;
    }
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 33)); // Set transparency color
    leftSpriteSheet = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    frameWidth = loadedSurface->w / 7; // Assuming 7 frames in a row
    frameHeight = loadedSurface->h / 4; // Assuming 4 rows (2 for left, 2 for right)
    SDL_FreeSurface(loadedSurface);

    loadedSurface = IMG_Load(rightPath.c_str());
    if (loadedSurface == nullptr) {
        return false;
    }
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 33)); // Set transparency color
    rightSpriteSheet = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    return leftSpriteSheet != nullptr && rightSpriteSheet != nullptr;
}

void Enemy::update(const Fish& fish) {
    int fishX = fish.getX();
    int fishY = fish.getY();

    // Interpolate the enemy's position towards the fish's position
    posX += static_cast<int>((fishX - posX) * 0.05f); // Increase speed to make Enemy follow Fish closely
    posY += static_cast<int>((fishY - posY) * 0.05f);

    // Update enemy state and direction
    if (fishX < posX) {
        setDirection(EnemyDirection::LEFT);
    }
    else {
        setDirection(EnemyDirection::RIGHT);
    }

    if (fishX == posX && fishY == posY) {
        setState(EnemyState::IDLE);
    }
    else {
        setState(EnemyState::MOVING);
    }

    updateAnimation();
}

void Enemy::render(SDL_Renderer* renderer) {
    SDL_Texture* currentSpriteSheet = (dir == EnemyDirection::LEFT) ? leftSpriteSheet : rightSpriteSheet;
    if (currentSpriteSheet != nullptr) {
        SDL_Rect srcRect = { frameWidth * currentFrame, frameHeight * (dir == EnemyDirection::LEFT ? 1 : 2), frameWidth, frameHeight };
        SDL_Rect renderQuad = { posX - frameWidth / 4, posY - frameHeight / 4, frameWidth / 2, frameHeight / 2 }; // Scale down by half
        SDL_RenderCopy(renderer, currentSpriteSheet, &srcRect, &renderQuad);
    }
}

void Enemy::freeSpriteSheet() {
    if (leftSpriteSheet != nullptr) {
        SDL_DestroyTexture(leftSpriteSheet);
        leftSpriteSheet = nullptr;
    }
    if (rightSpriteSheet != nullptr) {
        SDL_DestroyTexture(rightSpriteSheet);
        rightSpriteSheet = nullptr;
    }
}

void Enemy::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

int Enemy::getX() const {
    return posX;
}

int Enemy::getY() const {
    return posY;
}

void Enemy::setDirection(EnemyDirection d) {
    dir = d;
}

EnemyDirection Enemy::getDirection() const {
    return dir;
}

void Enemy::setState(EnemyState s) {
    state = s;
}

EnemyState Enemy::getState() const {
    return state;
}

SDL_Rect Enemy::getRect() const {
    SDL_Rect rect = { posX - frameWidth / 4, posY - frameHeight / 4, frameWidth / 2, frameHeight / 2 }; // Scale down by half
    return rect;
}

void Enemy::updateAnimation() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > lastFrameTime + 100) { // Change frame every 100ms (faster speed)
        lastFrameTime = currentTime;

        if (state == EnemyState::IDLE) {
            if (dir == EnemyDirection::LEFT) {
                if (currentFrame < 0 || currentFrame > 4) {
                    currentFrame = 0;
                }
                currentFrame++;
                if (currentFrame > 4) {
                    currentFrame = 4;
                    dir = EnemyDirection::RIGHT;
                }
            }
            else if (dir == EnemyDirection::RIGHT) {
                if (currentFrame < 2 || currentFrame > 6) {
                    currentFrame = 6;
                }
                currentFrame--;
                if (currentFrame < 2) {
                    currentFrame = 2;
                    dir = EnemyDirection::LEFT;
                }
            }
        }
        else {
            currentFrame += frameDirection;
            if (currentFrame == 6 || currentFrame == 0) {
                frameDirection = -frameDirection;
            }
        }
    }
}



