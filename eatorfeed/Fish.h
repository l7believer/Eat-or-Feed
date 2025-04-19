#ifndef FISH_H
#define FISH_H

#include <SDL.h>
#include <string>



class Fish {
public:
    Fish();
    void loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer); // tải sprite
    void updatePosition(int mouseX, int mouseY); //update vị trí
    void render(SDL_Renderer* renderer, SDL_Rect camera); //render fish
    void moveByDelta(int dx, int dy); //Hàm di chuyển cá
    float getX() const; 
    float getY() const;
    //Update tọa độ
	SDL_Rect getCollisionBox() const; //lấy box va chạm
    bool isEating = false;
    int eatFrame = 0;
    int eatFrameTime = 0;


private:
    float x, y;
    float speed;
    int currentFrame;  //Sprite move
    int frameTime; //Thời gian delay frame
    bool facingLeft; //Hướng
    SDL_Texture* spriteLeft; //Quay trái
    SDL_Texture* spriteRight; //Quay phải
    int turnFrameTime; //Delay quay đầu frame
    bool isTurning; //trạng thái quay đầu
    int turnFrame; //Sprite quay đầu
    int turnDirection; // 1: trái -> phải, -1: phải -> trái
    
};

#endif
