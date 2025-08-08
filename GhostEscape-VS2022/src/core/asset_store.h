#pragma once
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

class AssetStore
{
    SDL_Renderer *renderer_ = nullptr;
    std::unordered_map<std::string, SDL_Texture *> textures_;
    std::unordered_map<std::string, Mix_Chunk *> sounds_;
    std::unordered_map<std::string, Mix_Music *> music_;
    std::unordered_map<std::string, TTF_Font *> fonts_;

public:
    AssetStore(SDL_Renderer *renderer) { renderer_ = renderer; };
    ~AssetStore() = default;

    // Load
    void loadImage(const std::string &file_path);
    void loadSound(const std::string &file_path);
    void loadMusic(const std::string &file_path);
    void loadFont(const std::string &file_path, int font_size);

    // read
    SDL_Texture *getImage(const std::string &file_path);
    Mix_Chunk *getSound(const std::string &file_path);
    Mix_Music *getMusic(const std::string &file_path);
    TTF_Font *getFont(const std::string &file_path, int font_size);

    void clean();
};