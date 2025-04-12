#ifndef FISH_H
#define FISH_H

#include <SDL.h>
#include <string>

class Fish {
public:
    Fish();
    void loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer);
    void updatePosition(int mouseX, int mouseY);
    void render(SDL_Renderer* renderer);
    void moveByDelta(int dx, int dy);
    float getX() const;
    float getY() const;
    //
    bool isTurning;
    int turnFrame;
    int turnDirection; // 1: trái -> phải, -1: phải -> trái


private:
    float x, y;
    float speed;
    int currentFrame;
    int frameTime;
    bool facingLeft;
    SDL_Texture* spriteLeft;
    SDL_Texture* spriteRight;

    int turnFrameTime;
};

#endif
