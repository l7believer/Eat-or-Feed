#include "Fish.h"
#include <SDL_image.h>
#include <cmath>
#include "Constants.h"


Fish::Fish()
    : x(BACKGROUND_WIDTH / 2), y(BACKGROUND_HEIGHT / 2), speed(0.05f), currentFrame(0), frameTime(0), //speed
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


//void Fish::updatePosition(int mouseX, int mouseY) {
//    float dx = mouseX - x;
//    float dy = mouseY - y;
//    float distance = sqrt(dx * dx + dy * dy);
//
//    bool newFacingLeft = dx < 0;
//
//    if (!isTurning && newFacingLeft != facingLeft) {
//        isTurning = true;
//        turnFrame = 0;
//        turnFrameTime = 0;
//        turnDirection = (facingLeft && !newFacingLeft) ? 1 : -1;
//    }
//
//    if (distance > 1) {
//        float dirX = dx / distance;
//        float dirY = dy / distance;
//
//        x += dirX * speed * 10;
//        y += dirY * speed * 10;
//
//        // Chỉ cập nhật hướng khi không đang quay
//        if (!isTurning) {
//            facingLeft = newFacingLeft;
//        }
//    }
//
//
//    if (distance > 1) {
//        x += dx * speed;
//        y += dy * speed;
//        facingLeft = newFacingLeft;
//    }
//}
//void Fish::updatePosition(int mouseX, int mouseY) {
//    float dx = mouseX - x;
//    float dy = mouseY - y;
//    float distance = sqrt(dx * dx + dy * dy);
//
//    bool newFacingLeft = dx < 0;
//
//    if (!isTurning && newFacingLeft != facingLeft) {
//        isTurning = true;
//        turnFrame = 0;
//        turnFrameTime = 0;
//        turnDirection = (facingLeft && !newFacingLeft) ? 1 : -1;
//    }
//
//    //if (distance > 1) {
//    //    float dirX = dx / distance;
//    //    float dirY = dy / distance;
//
//    //    x += dirX * speed ;
//    //    y += dirY * speed ;
//
//    //    // Chỉ cập nhật hướng khi không đang quay
//    //    if (!isTurning) {
//    //        facingLeft = newFacingLeft;
//    //    }
//    //}
//
//    if (distance > 1) {
//        x += dx * speed;
//        y += dy * speed;
//        facingLeft = newFacingLeft;
//    }
//}
//void Fish::updatePosition(int mouseX, int mouseY) {
//    float dx = mouseX - x;
//    float dy = mouseY - y;
//    float distance = sqrt(dx * dx + dy * dy);
//
//    bool newFacingLeft = dx < 0;
//
//    if (!isTurning && newFacingLeft != facingLeft) {
//        isTurning = true;
//        turnFrame = 0;
//        turnFrameTime = 0;
//        turnDirection = (facingLeft && !newFacingLeft) ? 1 : -1;
//    }
//
//    if (distance > 1) {
//        // Chuẩn hóa vector hướng
//        float dirX = dx / distance;
//        float dirY = dy / distance;
//
//        // Di chuyển cá với tốc độ cố định
//        x += dirX * speed * 1000; // Tăng tốc độ nếu cần
//        y += dirY * speed * 1000;
//
//        // Cập nhật hướng nếu không đang quay
//        if (!isTurning) {
//            facingLeft = newFacingLeft;
//        }
//    }
//}
void Fish::updatePosition(int mouseX, int mouseY) {
    float dx = mouseX - x;
    float dy = mouseY - y;
    float distance = sqrt(dx * dx + dy * dy);

    // Ngưỡng tối thiểu để xác định khi nào cá cần di chuyển
    const float distanceThreshold = 50.0f;

    // Nếu khoảng cách quá nhỏ, không thay đổi hướng hoặc di chuyển
    if (distance < distanceThreshold) {
        return;
    }

    bool newFacingLeft = dx < 0;

    // Nếu hướng mới khác hướng hiện tại và cá không đang quay đầu
    if (!isTurning && newFacingLeft != facingLeft) {
        isTurning = true;
        turnFrame = 0;
        turnFrameTime = 0;
        turnDirection = (facingLeft && !newFacingLeft) ? 1 : -1;
    }

    // Chuẩn hóa vector hướng
    float dirX = dx / distance;
    float dirY = dy / distance;

    // Di chuyển cá với tốc độ cố định
    x += dirX * speed * 500;
    y += dirY * speed * 500;

    // Cập nhật hướng nếu không đang quay
    if (!isTurning) {
        facingLeft = newFacingLeft;
    }
}




//void Fish::render(SDL_Renderer* renderer) {
//    SDL_Texture* currentSprite = facingLeft ? spriteLeft : spriteRight;
//    const int FRAME_WIDTH = 3616/15;
//    const int FRAME_HEIGHT = 485/4;
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
            column * FRAME_WIDTH,
            row * FRAME_HEIGHT,
            FRAME_WIDTH,
            FRAME_HEIGHT
        };

        // Chậm lại ở đây
        turnFrameTime++;
        if (turnFrameTime >= 1.5f) { // tăng lên sẽ làm animation quay đầu chậm hơn
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
        int seq[] = { 0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
        static const int SEQ_LENGTH = sizeof(seq) / sizeof(int);

        frameTime++;
        if (frameTime >= 3) {
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

    /*SDL_Rect destRect = {
    static_cast<int>(x - (FRAME_WIDTH / 4)),
    static_cast<int>(y - (FRAME_HEIGHT / 4)),
    FRAME_WIDTH / 2,
    FRAME_HEIGHT / 2
    };*/
    SDL_Rect destRect = {
    static_cast<int>(x - FRAME_WIDTH / 4) - camera.x,
    static_cast<int>(y - FRAME_HEIGHT / 4) - camera.y,
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

