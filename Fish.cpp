#include "Fish.h"
#include <SDL_image.h>

Fish::Fish() : leftSpriteSheet(nullptr), rightSpriteSheet(nullptr), frameWidth(0), frameHeight(0), currentFrame(0), frameDirection(1), lastFrameTime(0), state(FishState::IDLE), dir(FishDirection::RIGHT), posX(0), posY(0) {}

Fish::~Fish() {
    freeSpriteSheet();
}

bool Fish::loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer) {
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

void Fish::update() {
    updateAnimation();
}

void Fish::render(SDL_Renderer* renderer) {
    SDL_Texture* currentSpriteSheet = (dir == FishDirection::LEFT) ? leftSpriteSheet : rightSpriteSheet;
    if (currentSpriteSheet != nullptr) {
        SDL_Rect srcRect = { frameWidth * currentFrame, frameHeight * (dir == FishDirection::LEFT ? 1 : 2), frameWidth, frameHeight };
        SDL_Rect renderQuad = { posX - frameWidth / 4, posY - frameHeight / 4, frameWidth / 2, frameHeight / 2 }; // Scale down by half
        SDL_RenderCopy(renderer, currentSpriteSheet, &srcRect, &renderQuad);
    }
}

void Fish::freeSpriteSheet() {
    if (leftSpriteSheet != nullptr) {
        SDL_DestroyTexture(leftSpriteSheet);
        leftSpriteSheet = nullptr;
    }
    if (rightSpriteSheet != nullptr) {
        SDL_DestroyTexture(rightSpriteSheet);
        rightSpriteSheet = nullptr;
    }
}

void Fish::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

int Fish::getX() const {
    return posX;
}

int Fish::getY() const {
    return posY;
}

void Fish::setDirection(FishDirection d) {
    dir = d;
}

FishDirection Fish::getDirection() const {
    return dir;
}

void Fish::setState(FishState s) {
    state = s;
}

FishState Fish::getState() const {
    return state;
}

SDL_Rect Fish::getRect() const {
    SDL_Rect rect = { posX - frameWidth / 4, posY - frameHeight / 4, frameWidth / 2, frameHeight / 2 }; // Scale down by half
    return rect;
}

void Fish::updateAnimation() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > lastFrameTime + 100) { // Change frame every 100ms (faster speed)
        lastFrameTime = currentTime;
        currentFrame += frameDirection;
        if (currentFrame == 6 || currentFrame == 0) {
            frameDirection = -frameDirection;
        }
    }
}





