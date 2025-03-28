#pragma once
#include <SDL.h>
#include "Fish.h"

class Move {
public:
    Move();
    ~Move();
    void handleEvent(SDL_Event& e, Fish& fish);
    void update(Fish& fish);
    void render(SDL_Renderer* renderer, Fish& fish);

private:
    int mouseX, mouseY;
    float speed;
};









