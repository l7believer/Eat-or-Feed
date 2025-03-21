#include "Move.h"

Move::Move() : mouseX(0), mouseY(0), speed(0.0167f) {} // Reduced speed to 1/3

Move::~Move() {}

void Move::handleEvent(SDL_Event& e, Fish& fish) {
    if (e.type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&mouseX, &mouseY);
    }
}

void Move::update(Fish& fish) {
    int fishX = fish.getX();
    int fishY = fish.getY();

    // Interpolate the fish's position towards the mouse position
    fishX += static_cast<int>((mouseX - fishX) * speed);
    fishY += static_cast<int>((mouseY - fishY) * speed);

    fish.setPosition(fishX, fishY);

    // Update fish state and direction
    if (mouseX < fishX) {
        fish.setDirection(FishDirection::LEFT);
    }
    else {
        fish.setDirection(FishDirection::RIGHT);
    }

    if (mouseX == fishX && mouseY == fishY) {
        fish.setState(FishState::IDLE);
    }
    else {
        fish.setState(FishState::MOVING);
    }
}

void Move::render(SDL_Renderer* renderer, Fish& fish) {
    fish.update();
    fish.render(renderer);
}








