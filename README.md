# Eat or Feed
![Banner](https://scontent-hkg4-1.xx.fbcdn.net/v/t39.30808-6/493609300_1615695292412768_3105620646831643776_n.jpg?_nc_cat=100&ccb=1-7&_nc_sid=127cfc&_nc_eui2=AeF8hk86WgyH4RzwnlOw1-P3ZoYZcwnl28RmhhlzCeXbxNGKQpsmPlckPBYpzdSXcbRJZrzs6iJPk6oEeZSO8nz4&_nc_ohc=5-b9wP5uNY8Q7kNvwFKaKTF&_nc_oc=AdlneZRBHKzJiZo0h9KfxK6H7O8a0-9gXVZxF4CivxhZsrWufOcxRvFBi_txu-kbIDk&_nc_zt=23&_nc_ht=scontent-hkg4-1.xx&_nc_gid=ljvtTlbUcSLvBLC-Vk3SOg&oh=00_AfGsBKFKESas0Ya1zZNz2EeJOcCXbICKh-0DDG56BsULTQ&oe=68120975)

Eat or Feed là một game sinh tồn nơi mà bạn phải ăn để sống hoặc là bị ăn và bị loại bỏ.

Link demo game: https://drive.google.com/drive/folders/1VDs4TecH6vPSWrpKV7pOc7xyWSmYpjtH?usp=drive_link

---

## 📚 Mục lục

- [Cấu trúc dự án](#cấu-trúc-dự-án)
  - [Game.cpp](#1-gamecpp)
  - [Fish.cpp](#2-fishcpp)
  - [KethuX.cpp](#3-kethuxcpp)
- [Chức năng chính của game](#chức-năng-chính-của-game)
- [Tải game chính thức](#tải-game-chính-thức)
- [Tài nguyên đã sử dụng](#tài-nguyên-đã-sử-dụng)
  
---

## Cấu trúc dự án

### 1. **Game.cpp**
Quản lý logic chính của trò chơi, bao gồm khởi tạo, xử lý sự kiện, render, và vòng lặp chính.

#### **Các hàm chính trong `Game.cpp`:**

- **`Game::Game()`**  
  Constructor khởi tạo các biến thành viên mặc định như `window`, `renderer`, `backgroundTexture`, `quit`, `isPaused`, và `score`.

- **`Game::~Game()`**  
  Destructor gọi hàm `close()` để giải phóng tài nguyên.

- **`bool Game::init()`**  
  - Khởi tạo SDL, SDL_image, SDL_ttf, và SDL_mixer.  
  - Tạo cửa sổ và renderer.  
  - Tải các tài nguyên như hình ảnh, âm thanh, và font chữ.  
  - Khởi tạo các đối tượng kẻ thù (`Kethu1` đến `Kethu12`) và cá của người chơi.

- **`void Game::handleEvents()`**  
  - Xử lý các sự kiện như nhấp chuột, nhấn phím, và thoát trò chơi.  
  - Quản lý trạng thái game (menu, chơi, tạm dừng, thắng, thua).  
  - Cập nhật trạng thái tăng tốc của cá.

- **`void Game::render()`**  
  - Render các thành phần của trò chơi như background, kẻ thù, cá, và giao diện.  
  - Hiển thị điểm số và các kẻ thù mà người chơi có thể ăn.

- **`void Game::run()`**  
  - Vòng lặp chính của trò chơi, gọi các hàm `handleEvents()`, `updateCamera()`, và `render()`.

- **`void Game::close()`**  
  - Giải phóng tài nguyên như texture, renderer, âm thanh, và font chữ.

- **`void Game::updateCamera()`**  
  - Cập nhật vị trí camera để theo dõi cá của người chơi.

- **`void Game::resetGame()`**  
  - Đặt lại trạng thái trò chơi, bao gồm vị trí cá, camera, điểm số, và danh sách kẻ thù.

- **`void Game::renderMenu()`**  
  - Render giao diện menu chính.

- **`void Game::renderPause()`**  
  - Render giao diện tạm dừng.

- **`void Game::renderYouWin()`**  
  - Render giao diện khi người chơi thắng.

- **`void Game::renderYouLose()`**  
  - Render giao diện khi người chơi thua.

---

### 2. **Fish.cpp**
Quản lý hành vi và trạng thái của cá.

#### **Các hàm chính trong `Fish.cpp`:**

- **`Fish::Fish()`**  
  Constructor khởi tạo các biến như vị trí, kích thước, tốc độ, và trạng thái ăn.

- **`void Fish::loadSpriteSheet()`**  
  - Tải sprite cho cá khi di chuyển sang trái và phải.

- **`void Fish::updatePosition(int mouseX, int mouseY)`**  
  - Cập nhật vị trí của cá dựa trên tọa độ chuột.

- **`void Fish::startBoost()`**  
  - Kích hoạt trạng thái tăng tốc.

- **`void Fish::updateBoost()`**  
  - Cập nhật thời gian và trạng thái tăng tốc.

- **`void Fish::setScale(float scale)`**  
  - Thay đổi kích thước của cá dựa trên số điểm.

- **`SDL_Rect Fish::getCollisionBox()`**  
  - Trả về hình chữ nhật đại diện cho vùng va chạm của cá.

- **`void Fish::render(SDL_Renderer* renderer, SDL_Rect& camera)`**  
  - Render cá lên màn hình.

---

### 3. **KethuX.cpp (nhiều Kethu)**
Tệp này quản lý hành vi của kẻ thù loại `KethuX`.

#### **Các hàm chính trong `KethuX.cpp`:**

- **`KethuX::KethuX()`**  
  Constructor khởi tạo các biến như vị trí, kích thước, tốc độ, và trạng thái ăn.

- **`void KethuX::loadSpriteSheet()`**  
  - Tải sprite cho kẻ thù khi di chuyển sang trái và phải.

- **`void KethuX::setRandomTarget()`**  
  - Chọn 1 vị trí ngẫu nhiên trên background.
 
- **`void KethuX::moveToTarget()`**  
  - Di chuyển đến vị trí ngẫu nhiên đã chọn
 
- **`void KethuX::updatePosition()`**  
  - Cập nhật vị trí của kẻ thù dựa trên logic di chuyển.

- **`SDL_Rect KethuX::getCollisionBox()`**  
  - Trả về hình chữ nhật đại diện cho vùng va chạm của kẻ thù.

- **`void KethuX::reset()`**  
  - Đặt lại vị trí và trạng thái của kẻ thù sau khi bị ăn.

- **`void KethuX::render(SDL_Renderer* renderer, SDL_Rect& camera)`**  
  - Render kẻ thù lên màn hình.

---

## Chức năng chính của game

1. **Điều khiển cá**: Người chơi điều khiển cá bằng chuột và có thể tăng tốc bằng cách nhấp chuột trái.  
2. **Ăn kẻ thù nhỏ hơn**: Làm cho cá lớn hơn bằng cách ăn các kẻ thù nhỏ hơn.  
3. **Tránh kẻ thù lớn hơn**: Tránh xa các kẻ thù lớn hơn cá của bạn.  
4. **Thắng trò chơi**: Đạt được điểm số 1000 để chiến thắng.  
5. **Trạng thái game**: Bao gồm menu, chơi, tạm dừng, thắng, và thua.

---

## 🔗 Tải game chính thức

📦 **Phiên bản phát hành v1.0**:  
👉 [Tải từ GitHub Releases](https://github.com/l7believer/Eat-or-Feed/releases/tag/v1.0)

---

## Tài nguyên đã sử dụng

- **Mã nguồn tham khảo**:  
  *Chatgpt*

- **Icon**:  
  *(https://www.steamgriddb.com/game/5263822/icons)*

- **Đồ họa**:  
  *(https://www.spriters-resource.com/pc_computer/feedingfrenzy/)*

---
