#include "Fish.h"
#include <SDL_image.h>
#include <cmath>
#include "Constants.h"


Fish::Fish()
    : x(BACKGROUND_WIDTH / 2), y(BACKGROUND_HEIGHT / 2), speed(0.05f), currentFrame(0), frameTime(0),
    facingLeft(true), isTurning(false), turnFrame(0), turnFrameTime(0), turnDirection(0) {
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

    // Không di chuyển khi distence <
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

    // Speed cố định
    x += dirX * speed * 400;
    y += dirY * speed * 400;

    // Cập nhật hướng nếu không đang quay
    if (!isTurning) {
        facingLeft = newFacingLeft;
    }
}

void Fish::render(SDL_Renderer* renderer, SDL_Rect camera) {
    SDL_Texture* currentSprite = facingLeft ? spriteLeft : spriteRight;
    const int frameWidth = 3616 / 15;
    const int frameHeight = 485 / 4;
    SDL_Rect srcRect;

    if (isTurning) {
        int row = 3;
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
            column * frameWidth,
            row * frameHeight,
            frameWidth,
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
        int row = 2;
        int seq[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
        static const int SEQ_LENGTH = sizeof(seq) / sizeof(int);

        frameTime++;
        if (frameTime >= 3) {
            currentFrame = (currentFrame + 1) % SEQ_LENGTH;
            frameTime = 0;
        }

        int column = seq[currentFrame];

        srcRect = {
            column * frameWidth,
            row * frameHeight,
            frameWidth,
            frameHeight
        };
    }

  // giữ cá theo camera
    SDL_Rect destRect = {
    static_cast<int>(x - frameWidth / 4) - camera.x,
    static_cast<int>(y - frameHeight / 4) - camera.y,
    frameWidth/2,
    frameHeight/2
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

