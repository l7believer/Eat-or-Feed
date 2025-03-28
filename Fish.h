#pragma once
#include <SDL.h>
#include <string>

enum class FishState { IDLE, MOVING };
enum class FishDirection { LEFT, RIGHT };

class Fish {
public:
    Fish();
    ~Fish();
    bool loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer);
    void update();
    void render(SDL_Renderer* renderer);
    void freeSpriteSheet();
    void setPosition(int x, int y);
    int getX() const;
    int getY() const;
    void setDirection(FishDirection d);
    FishDirection getDirection() const;
    void setState(FishState s);
    FishState getState() const;
    SDL_Rect getRect() const;

private:
    SDL_Texture* leftSpriteSheet;
    SDL_Texture* rightSpriteSheet;
    int frameWidth, frameHeight;
    int currentFrame;
    int frameDirection;
    Uint32 lastFrameTime;
    FishState state;
    FishDirection dir;
    int posX, posY;
    void updateAnimation();
};



