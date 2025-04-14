#ifndef KETHU6_H
#define KETHU6_H

#include <SDL.h>
#include <string>

class Kethu6 {
public:
    Kethu6();
    void loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer); // Tải sprite
    void updatePosition(); // Di chuyển ngẫu nhiên
    void render(SDL_Renderer* renderer, SDL_Rect camera); // Render cá
    float getX() const;
    float getY() const;
    SDL_Rect getCollisionBox() const;
    void reset();

private:
    float x, y; // Vị trí hiện tại
    float targetX, targetY; // Tọa độ mục tiêu
    float speed; // Tốc độ di chuyển
    int currentFrame; // Sprite move
    int frameTime; // Thời gian delay frame
    bool facingLeft; // Hướng
    SDL_Texture* spriteLeft; // Quay trái
    SDL_Texture* spriteRight; // Quay phải

    // Quay đầu
    bool isTurning; // Trạng thái quay đầu
    int turnFrame; // Sprite quay đầu
    int turnFrameTime; // Thời gian delay frame quay đầu
    int turnDirection; // 1: trái -> phải, -1: phải -> trái

    void moveToTarget(); // Hàm di chuyển đến mục tiêu
    void setRandomTarget(); // Hàm chọn tọa độ mục tiêu ngẫu nhiên
};

#endif

