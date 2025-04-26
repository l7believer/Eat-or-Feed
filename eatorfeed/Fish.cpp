#include "Fish.h"
#include <SDL_image.h>
#include <cmath>
#include "Constants.h"


Fish::Fish()
    : x(BACKGROUND_WIDTH / 2), y(BACKGROUND_HEIGHT / 2), speed(0.02f), currentFrame(0), frameTime(0),
    facingLeft(true), isTurning(false), turnFrame(0), turnFrameTime(0), turnDirection(0), isEating(false), eatFrame(0), eatFrameTime(0),
    isBoosting(false), boostStartTime(0), lastBoostTime(0), scale(1.0f) { // Khởi tạo scale = 1.0
}

void Fish::setScale(float newScale) {
    scale = newScale;
}

float Fish::getScale() const {
    return scale;
}

void Fish::startBoost() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastBoostTime >= cooldownTime) {
        isBoosting = true;
        boostStartTime = currentTime;
        lastBoostTime = currentTime;
    }
}

void Fish::updateBoost() {
    if (isBoosting) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - boostStartTime >= boostDuration) {
            isBoosting = false;
        }
    }
}

void Fish::loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer) {
    SDL_Surface* leftSurface = IMG_Load(leftPath.c_str());
    SDL_Surface* rightSurface = IMG_Load(rightPath.c_str());

    SDL_SetColorKey(leftSurface, SDL_TRUE, SDL_MapRGB(leftSurface->format, 255, 255, 255));
    SDL_SetColorKey(rightSurface, SDL_TRUE, SDL_MapRGB(rightSurface->format, 255, 255, 255));

    spriteLeft = SDL_CreateTextureFromSurface(renderer, leftSurface);
    spriteRight = SDL_CreateTextureFromSurface(renderer, rightSurface);

    SDL_FreeSurface(leftSurface);
    SDL_FreeSurface(rightSurface);
}

void Fish::updatePosition(int mouseX, int mouseY) {
    float dx = mouseX - x;
    float dy = mouseY - y;
    float distance = sqrt(dx * dx + dy * dy);

    // Ngưỡng pixel để cá quay đầu (tránh quay đầu liên tục)
    const float distanceThreshold = 50.0f;

    if (distance < distanceThreshold) {
        return;
    }

    bool newFacingLeft = dx < 0;

    // Quay đầu cá
    if (!isTurning && newFacingLeft != facingLeft) {
        isTurning = true;
        turnFrame = 0;
        turnFrameTime = 0;
        turnDirection = (facingLeft && !newFacingLeft) ? 1 : -1;
    }

    // Chuẩn hóa vector hướng
    float dirX = dx / distance;
    float dirY = dy / distance;

    // Tăng tốc nếu đang trong trạng thái boost
    float currentSpeed = isBoosting ? speed * 2.0f : speed;

    x += dirX * currentSpeed * 400;
    y += dirY * currentSpeed * 400;

    if (!isTurning) {
        facingLeft = newFacingLeft;
    }
}

void Fish::render(SDL_Renderer* renderer, SDL_Rect camera) {
    SDL_Texture* currentSprite = facingLeft ? spriteLeft : spriteRight;
    const int frameWidth = 3616 / 15;
    const int frameHeight = 485 / 4;
    SDL_Rect srcRect;

    // Tính toán kích thước dựa trên scale
    int scaledWidth = static_cast<int>((frameWidth / 2) * scale);
    int scaledHeight = static_cast<int>((frameHeight / 2) * scale);

    if (isEating) {
        int row = 0;
        int column;

        if (facingLeft) {
            int seq[] = { 0, 1, 2, 3, 4, 5 }; // frame ăn khi quay trái
            column = seq[eatFrame];
            currentSprite = spriteLeft;
        }
        else {
            int seq[] = { 14, 13, 12, 11, 10, 9 }; // frame ăn khi quay phải
            column = seq[eatFrame];
            currentSprite = spriteRight;
        }

        srcRect = {
            column * frameWidth + 2,
            row * frameHeight + 2,
            frameWidth - 2,
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
            static_cast<int>(x - scaledWidth / 2) - camera.x,
            static_cast<int>(y - scaledHeight / 2) - camera.y,
            scaledWidth,
            scaledHeight
        };

        SDL_RenderCopy(renderer, currentSprite, &srcRect, &destRect);
        return;
    }

    if (isTurning) {
        int row = 3; // dòng 4 là sprite quay đầu
        int column;

        if (turnDirection == 1) { // trái -> phải
            int seq[] = { 0, 1, 2, 3, 4 };
            column = seq[turnFrame];
            currentSprite = spriteLeft;
        }
        else { // phải -> trái
            int seq[] = { 14, 13, 12, 11, 10 };
            column = seq[turnFrame];
            currentSprite = spriteRight;
        }

        srcRect = {
            column * frameWidth + 2,
            row * frameHeight + 2,
            frameWidth - 2,
            frameHeight - 2
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
        int row = 2; // dòng 3 là sprite di chuyển
        int seq[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
        static const int SEQ_LENGTH = sizeof(seq) / sizeof(int);

        frameTime++;
        if (frameTime >= 3) {
            currentFrame = (currentFrame + 1) % SEQ_LENGTH;
            frameTime = 0;
        }

        int column = seq[currentFrame];

        srcRect = {
            column * frameWidth + 2,
            row * frameHeight + 2,
            frameWidth - 2,
            frameHeight - 2
        };
    }

    SDL_Rect destRect = {
        static_cast<int>(x - scaledWidth / 2) - camera.x,
        static_cast<int>(y - scaledHeight / 2) - camera.y,
        scaledWidth,
        scaledHeight
    };

    SDL_RenderCopy(renderer, currentSprite, &srcRect, &destRect);
}

float Fish::getX() const { return x; }
float Fish::getY() const { return y; }

void Fish::moveByDelta(int dx, int dy) {
    x += dx * speed;
    y += dy * speed;
    facingLeft = dx < 0;
}

SDL_Rect Fish::getCollisionBox() const {
    const int frameWidth = 3616 / 15;
    const int frameHeight = 485 / 4;
    int scaledWidth = static_cast<int>(frameWidth * scale);
    int scaledHeight = static_cast<int>(frameHeight * scale);

    SDL_Rect box;
    if (facingLeft) {
        box = {
            static_cast<int>(x - scaledWidth / 4),
            static_cast<int>(y - scaledHeight / 8),
            scaledWidth / 4,
            scaledHeight / 4
        };
    }
    else {
        box = {
            static_cast<int>(x),
            static_cast<int>(y - scaledHeight / 8),
            scaledWidth / 4,
            scaledHeight / 4
        };
    }

    return box;
}



