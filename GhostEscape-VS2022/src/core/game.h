#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>
#include "asset_store.h"
#include <random>

struct Texture;
class Scene;

class Game
{
    Game() {};
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

    bool is_running_ = true;

    glm::vec2 screen_size_ = glm::vec2(0);

    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    TTF_TextEngine* ttf_engine_ = nullptr;

    Uint64 FPS_ = 60;
    Uint64 frame_delay_ = 0;
    float dt_ = 0.0f;

    Scene *current_scene_ = nullptr;

    AssetStore *asset_store_ = nullptr;

    std::mt19937 gen_ = std::mt19937(std::random_device{}());

    glm::vec2 mouse_position_ = glm::vec2(0);
    SDL_MouseButtonFlags mouse_buttons_ = 0;

    int score_ = 0;
    int high_score_ = 0;
public:
    static Game &getInstance()
    {
        static Game instance;
        return instance;
    }

    void run();
    void init(std::string title, int width, int height);
    void handleEvents();
    void update(float dt);
    void render();
    void clean();

    void renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2& mask = glm::vec2(1.0));
    void renderFillCircle(const glm::vec2 &position, const glm::vec2 &size, float alpha);
    void renderHBar(const glm::vec2 &position, const glm::vec2 &size, float percent, SDL_FColor fcolor);

    TTF_Text* CreateTTFText(const std::string& text, const std::string& font_path, int font_size = 16);

    // random number generater
    float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(gen_); }
    int randomInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(gen_); }
    glm::vec2 randomVec2(const glm::vec2 &min, const glm::vec2 &max) { return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y)); }
    glm::ivec2 randomIVec2(const glm::ivec2 &min, const glm::ivec2 &max) { return glm::ivec2(randomInt(min.x, max.x), randomInt(min.y, max.y)); }

    // 工具函数
    void drawGrid(const glm::vec2 &top_left, const glm::vec2 &botton_right, float grid_width, SDL_FColor fcolor);
    void drawBoundary(const glm::vec2 &top_left, const glm::vec2 &botton_right, float boundary_width, SDL_FColor fcolor);

    // getter
    auto getScreenSize() const { return screen_size_; }
    Scene *getCurrentScene() const { return current_scene_; }
    auto getAssetStore() const { return asset_store_; }
    glm::vec2 getMousePosition() const { return mouse_position_; }
    SDL_MouseButtonFlags getMouseButtons() const { return mouse_buttons_; }

    // setter

    // Score
    void setScore(int score);
    int getScore() const { return score_; }
    void setHighScore(int high_score) { high_score_ = high_score; }
    int getHighScore() const { return high_score_; }
    void addScore(int score);

    // sound
    void playMusic(const std::string& music_path, bool loop = true) { Mix_PlayMusic(asset_store_->getMusic(music_path), loop ? -1 : 0); } //-1 infinite loop
    void playSound(const std::string& sound_path) { Mix_PlayChannel(-1, asset_store_->getSound(sound_path), 0); }
    void stopMusic() { Mix_HaltMusic(); }
    void stopSound() { Mix_HaltChannel(-1); }       // all sound
    void pauseMusic() { Mix_PauseMusic(); }
    void pauseSound() { Mix_Pause(-1); }
    void resumeMusic() { Mix_ResumeMusic(); }
    void resumeSound() { Mix_Resume(-1); }
};