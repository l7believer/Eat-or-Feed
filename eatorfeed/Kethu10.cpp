#include "Kethu10.h"
#include <SDL_image.h>
#include <cstdlib>
#include <cmath>
#include "Constants.h"
#include <string>
#include "Game.h"

Kethu10::Kethu10()
    : x(1 * BACKGROUND_WIDTH), // x = 0 hoặc BACKGROUND_WIDTH
    y(rand() % BACKGROUND_HEIGHT),              // y ngẫu nhiên từ 0 đến BACKGROUND_HEIGHT
    targetX(rand() % BACKGROUND_WIDTH),         // targetX ngẫu nhiên
    targetY(rand() % BACKGROUND_HEIGHT),        // targetY ngẫu nhiên
    speed(0.01f), currentFrame(0), frameTime(0),
    facingLeft(x == BACKGROUND_WIDTH), // Nếu x = BACKGROUND_WIDTH, quay trái
    isTurning(false), turnFrame(0), turnFrameTime(0), turnDirection(0) {
}

void Kethu10::loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer) {
    SDL_Surface* leftSurface = IMG_Load(leftPath.c_str());
    SDL_Surface* rightSurface = IMG_Load(rightPath.c_str());

    SDL_SetColorKey(leftSurface, SDL_TRUE, SDL_MapRGB(leftSurface->format, 255, 255, 255));
    SDL_SetColorKey(rightSurface, SDL_TRUE, SDL_MapRGB(rightSurface->format, 255, 255, 255));

    spriteLeft = SDL_CreateTextureFromSurface(renderer, leftSurface);
    spriteRight = SDL_CreateTextureFromSurface(renderer, rightSurface);

    SDL_FreeSurface(leftSurface);
    SDL_FreeSurface(rightSurface);
}


void Kethu10::updatePosition() {
    moveToTarget();
}

void Kethu10::setRandomTarget() {
    targetX = rand() % BACKGROUND_WIDTH; // targetX ngẫu nhiên trong background
    targetY = rand() % BACKGROUND_HEIGHT; // targetY ngẫu nhiên trong background
}

void Kethu10::moveToTarget() {
    float dx = targetX - x;
    float dy = targetY - y;
    float distance = sqrt(dx * dx + dy * dy);

    // Nếu đã đến gần mục tiêu, chọn mục tiêu mới
    if (distance < 10) {
        setRandomTarget();
        return;
    }

    // Xác định hướng mới
    bool newFacingLeft = dx < 0;

    // Quay đầu nếu cần
    if (!isTurning && newFacingLeft != facingLeft) {
        isTurning = true;
        turnFrame = 0;
        turnFrameTime = 0;
        turnDirection = (facingLeft && !newFacingLeft) ? 1 : -1;
    }

    // Chuẩn hóa vector hướng
    float dirX = dx / distance;
    float dirY = dy / distance;

    // Di chuyển
    x += dirX * speed * 500;
    y += dirY * speed * 500;

    // Giới hạn vị trí trong background
    if (x < 0) x = 0;
    if (x > BACKGROUND_WIDTH) x = BACKGROUND_WIDTH;
    if (y < 0) y = 0;
    if (y > BACKGROUND_HEIGHT) y = BACKGROUND_HEIGHT;

    // Cập nhật hướng nếu không đang quay
    if (!isTurning) {
        facingLeft = newFacingLeft;
    }
}

void Kethu10::render(SDL_Renderer* renderer, SDL_Rect camera) {
    SDL_Texture* currentSprite = facingLeft ? spriteLeft : spriteRight;
    const int frameWidth = 5264 / 14;
    const int frameHeight = 424 / 3;
    SDL_Rect srcRect;

    if (isEating) {
        int row = 0;
        int column;

        if (facingLeft) {
            int seq[] = { 0, 1, 2, 3, 4, 5 }; // frame ăn khi quay trái
            column = seq[eatFrame];
            currentSprite = spriteLeft;
        }
        else {
            int seq[] = { 13, 12, 11, 10, 9, 8 }; // frame ăn khi quay phải
            column = seq[eatFrame];
            currentSprite = spriteRight;
        }

        srcRect = {
            column * frameWidth + 2,
            row * frameHeight + 2,
            frameWidth - 4,
            frameHeight - 2
        };

        eatFrameTime++;
        if (eatFrameTime >= 1) {
            eatFrame++;
            eatFrameTime = 0;
        }

        if (eatFrame >= 6) {
            isEating = false;
        }

        SDL_Rect destRect = {
            static_cast<int>(x - camera.x),
            static_cast<int>(y - camera.y),
            frameWidth / 2,
            frameHeight / 2
        };

        SDL_RenderCopy(renderer, currentSprite, &srcRect, &destRect);
        return;
    }

    if (isTurning) {
        int row = 2;
        int column;

        if (turnDirection == 1) { // trái -> phải
            int seq[] = { 0, 1, 2, 3, 4 };
            column = seq[turnFrame];
            currentSprite = spriteLeft;
        }
        else { // phải -> trái
            int seq[] = { 13, 12, 11, 10, 9 };
            column = seq[turnFrame];
            currentSprite = spriteRight;
        }

        srcRect = {
            column * frameWidth + 10,
            row * frameHeight,
            frameWidth - 20,
            frameHeight
        };

        turnFrameTime++;
        if (turnFrameTime >= 1.5f) { // thời gian quay đầu
            turnFrame++;
            turnFrameTime = 0;
        }

        if (turnFrame >= 5) {
            isTurning = false;
            facingLeft = (turnDirection == -1);
        }
    }
    else {
        int row = 1;
        int seq[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
        static const int SEQ_LENGTH = sizeof(seq) / sizeof(int);

        frameTime++;
        if (frameTime >= 3) {
            currentFrame = (currentFrame + 1) % SEQ_LENGTH;
            frameTime = 0;
        }

        int column = seq[currentFrame];

        srcRect = {
            column * frameWidth + 10,
            row * frameHeight,
            frameWidth - 20,
            frameHeight
        };
    }

    SDL_Rect destRect = {
    static_cast<int>(x - camera.x),
    static_cast<int>(y - camera.y),
    frameWidth / 2,
    frameHeight / 2
    };


    SDL_RenderCopy(renderer, currentSprite, &srcRect, &destRect);
}

float Kethu10::getX() const { return x; }
float Kethu10::getY() const { return y; }

SDL_Rect Kethu10::getCollisionBox() const {
    const int frameWidth = 5264 / 14;
    const int frameHeight = 424 / 3;

    SDL_Rect box;
    if (facingLeft) {
        box = {
            static_cast<int>(x),
            static_cast<int>(y + frameHeight / 8),
            frameWidth / 4,
            frameHeight / 4
        };
    }
    else {
        box = {
            static_cast<int>(x + frameWidth / 4),
            static_cast<int>(y + frameHeight / 8),
            frameWidth / 4,
            frameHeight / 4
        };
    }

    return box;
}

void Kethu10::reset() {
    // Reset vị trí giống như constructor
    x = (rand() % 1) * BACKGROUND_WIDTH;
    y = rand() % BACKGROUND_HEIGHT;

    // Target ngẫu nhiên
    targetX = rand() % BACKGROUND_WIDTH;
    targetY = rand() % BACKGROUND_HEIGHT;

    // Hướng quay
    facingLeft = (x == BACKGROUND_WIDTH);
    isTurning = false;
    turnFrame = 0;
    turnFrameTime = 0;
    turnDirection = 0;
}