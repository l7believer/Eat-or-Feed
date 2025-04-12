//#include "Kethu1.h"
//#include <SDL_image.h>
//
//Kethu1::Kethu1()
//    : leftTexture(nullptr), rightTexture(nullptr), frame(0), posX(400), posY(300), // random vi tri
//    speed(4), movingLeft(true), frameWidth(1007 / 8), frameHeight(425 / 4) {
//}
//
//Kethu1::~Kethu1() {
//    freeSpriteSheet();
//}
//
//bool Kethu1::loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer) {
//    SDL_Surface* leftSurface = IMG_Load(leftPath.c_str());
//    SDL_Surface* rightSurface = IMG_Load(rightPath.c_str());
//
//    if (!leftSurface || !rightSurface) return false;
//
//    // Xóa màu trắng (RGB 255,255,255)
//    SDL_SetColorKey(leftSurface, SDL_TRUE, SDL_MapRGB(leftSurface->format, 255, 255, 255));
//    SDL_SetColorKey(rightSurface, SDL_TRUE, SDL_MapRGB(rightSurface->format, 255, 255, 255));
//
//    leftTexture = SDL_CreateTextureFromSurface(renderer, leftSurface);
//    rightTexture = SDL_CreateTextureFromSurface(renderer, rightSurface);
//
//    SDL_FreeSurface(leftSurface);
//    SDL_FreeSurface(rightSurface);
//
//    return leftTexture && rightTexture;
//}
//
//
//void Kethu1::freeSpriteSheet() {
//    if (leftTexture) SDL_DestroyTexture(leftTexture);
//    if (rightTexture) SDL_DestroyTexture(rightTexture);
//    leftTexture = rightTexture = nullptr;
//}
//
//void Kethu1::updatePosition(int mouseX, int mouseY) {
//    if (mouseX < posX) { movingLeft = true; posX -= speed; }
//    else if (mouseX > posX) { movingLeft = false; posX += speed; }
//
//    if (mouseY < posY) posY -= speed;
//    else if (mouseY > posY) posY += speed;
//}
//
//void Kethu1::updateAnimation() {
//    frame = (frame + 1) % 15;
//    int column, row = 3;
//
//    if (movingLeft) {
//        int seq[] = { 0,1,2,3,4,5,6,7,6,5,4,3,2,1,0 };
//        column = seq[frame];
//    }
//    else {
//        int seq[] = { 7,6,5,4,3,2,1,0,1,2,3,4,5,6,7 };
//        column = seq[frame];
//    }
//
//    currentClip = { column * frameWidth, (row - 1) * frameHeight, frameWidth, frameHeight };
//}
//
//void Kethu1::render(SDL_Renderer* renderer) {
//    updateAnimation();
//    SDL_Texture* currentTexture = movingLeft ? leftTexture : rightTexture;
//    int scale = 2; // kich thuoc chia 2
//    SDL_Rect renderQuad = { posX, posY, frameWidth / scale, frameHeight / scale };
//
//    SDL_RenderCopy(renderer, currentTexture, &currentClip, &renderQuad);
//}
