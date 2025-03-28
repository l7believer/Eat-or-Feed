#pragma once
#include <SDL.h>
#include <string>
#include "Fish.h"

enum class EnemyState { IDLE, MOVING };
enum class EnemyDirection { LEFT, RIGHT };

class Enemy {
public:
    Enemy();
    ~Enemy();
    bool loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer);
    void update(const Fish& fish);
    void render(SDL_Renderer* renderer);
    void freeSpriteSheet();
    void setPosition(int x, int y);
    int getX() const;
    int getY() const;
    void setDirection(EnemyDirection d);
    EnemyDirection getDirection() const;
    void setState(EnemyState s);
    EnemyState getState() const;
    SDL_Rect getRect() const;

private:
    SDL_Texture* leftSpriteSheet;
    SDL_Texture* rightSpriteSheet;
    int frameWidth, frameHeight;
    int currentFrame;
    int frameDirection;
    Uint32 lastFrameTime;
    EnemyState state;
    EnemyDirection dir;
    int posX, posY;
    void updateAnimation();
};


