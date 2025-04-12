#include "Fish.h"
#include <SDL_image.h>
#include <cmath>
#include "Constants.h"

Fish::Fish()
    : x(0), y(0), speed(0.05f), currentFrame(0), frameTime(0),
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

    bool newFacingLeft = dx < 0;

    if (!isTurning && newFacingLeft != facingLeft) {
        isTurning = true;
        turnFrame = 0;
        turnFrameTime = 0;
        turnDirection = (facingLeft && !newFacingLeft) ? 1 : -1;
    }

    if (isTurning) return;

    if (distance > 1) {
        x += dx * speed;
        y += dy * speed;
        facingLeft = newFacingLeft;
    }
}

void Fish::render(SDL_Renderer* renderer) {
    SDL_Texture* currentSprite = facingLeft ? spriteLeft : spriteRight;
    const int FRAME_WIDTH = 241;
    const int FRAME_HEIGHT = 121;

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
            int seq[] = { 6, 5, 4, 3, 2 };
            column = seq[turnFrame];
            currentSprite = spriteRight;
        }

        srcRect = {
            column * FRAME_WIDTH,
            row * FRAME_HEIGHT,
            FRAME_WIDTH,
            FRAME_HEIGHT
        };

        // Chậm lại ở đây
        turnFrameTime++;
        if (turnFrameTime >= 3) { // tăng lên sẽ làm animation quay đầu chậm hơn
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
        int seq[] = { 0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1 };
        static const int SEQ_LENGTH = sizeof(seq) / sizeof(int);

        frameTime++;
        if (frameTime >= 5) {
            currentFrame = (currentFrame + 1) % SEQ_LENGTH;
            frameTime = 0;
        }

        int column = seq[currentFrame];

        srcRect = {
            column * FRAME_WIDTH,
            row * FRAME_HEIGHT,
            FRAME_WIDTH,
            FRAME_HEIGHT
        };
    }

    SDL_Rect destRect = {
        static_cast<int>(x),
        static_cast<int>(y),
        FRAME_WIDTH / 2,
        FRAME_HEIGHT / 2
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

