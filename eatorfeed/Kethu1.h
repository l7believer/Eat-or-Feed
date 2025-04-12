//#pragma once
//#include <SDL.h>
//#include <string>
//
//class Kethu1 {
//public:
//    Kethu1();
//    ~Kethu1();
//
//    bool loadSpriteSheet(const std::string& leftPath, const std::string& rightPath, SDL_Renderer* renderer);
//    void spawnAtEdge(int screenWidth, int screenHeight); // Xuất hiện ở cạnh ngẫu nhiên
//    void updateRandom();
//    void render(SDL_Renderer* renderer);
//    SDL_Rect getRect() const; // Để kiểm tra va chạm nếu cần
//
//
//private:
//    SDL_Texture* leftTexture;
//    SDL_Texture* rightTexture;
//    SDL_Rect currentClip;
//    int frame;
//    int posX, posY;
//    int speed;
//    bool movingLeft;
//    int frameWidth;
//    int frameHeight;
//
//    void updateAnimation();
//    void freeSpriteSheet();
//};
