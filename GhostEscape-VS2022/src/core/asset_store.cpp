#include "asset_store.h"

void AssetStore::loadImage(const std::string &file_path)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer_, file_path.c_str());
    if (texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image:%s\n", file_path.c_str());
        return;
    }

    textures_.emplace(file_path, texture);
}

void AssetStore::loadSound(const std::string &file_path)
{
    Mix_Chunk *sound = Mix_LoadWAV(file_path.c_str());
    if (sound == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sound:%s\n", file_path.c_str());
        return;
    }

    sounds_.emplace(file_path, sound);
}

void AssetStore::loadMusic(const std::string &file_path)
{
    Mix_Music *music = Mix_LoadMUS(file_path.c_str());
    if (music == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music:%s\n", file_path.c_str());
        return;
    }

    music_.emplace(file_path, music);
}

void AssetStore::loadFont(const std::string &file_path, int font_size)
{
    TTF_Font *font = TTF_OpenFont(file_path.c_str(), font_size);
    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font:%s\n", file_path.c_str());
        return;
    }

    fonts_.emplace(file_path + std::to_string(font_size), font);
}

SDL_Texture *AssetStore::getImage(const std::string &file_path)
{
    auto iter = textures_.find(file_path);
    if (iter == textures_.end())
    {
        // SDL_Log("Loading image: %s", file_path.c_str());
        loadImage(file_path);
        iter = textures_.find(file_path);
    }
    if (iter == textures_.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get image:%s\n", file_path.c_str());
        return nullptr;
    }
    // SDL_Log("Successfully got image: %s", file_path.c_str());
    return iter->second;
}

Mix_Chunk *AssetStore::getSound(const std::string &file_path)
{
    auto iter = sounds_.find(file_path);
    if (iter == sounds_.end())
    {
        loadSound(file_path);
        iter = sounds_.find(file_path);
    }
    if (iter == sounds_.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get sound:%s\n", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

Mix_Music *AssetStore::getMusic(const std::string &file_path)
{
    auto iter = music_.find(file_path);
    if (iter == music_.end())
    {
        loadMusic(file_path);
        iter = music_.find(file_path);
    }
    if (iter == music_.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get music:%s\n", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

TTF_Font *AssetStore::getFont(const std::string &file_path, int font_size)
{
    auto iter = fonts_.find(file_path + std::to_string(font_size));
    if (iter == fonts_.end())
    {
        loadFont(file_path, font_size);
        iter = fonts_.find(file_path + std::to_string(font_size));
    }
    if (iter == fonts_.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get font:%s\n", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

void AssetStore::clean()
{

    for (auto &texture : textures_)
    {
        SDL_DestroyTexture(texture.second);
    }
    textures_.clear();

    for (auto &sounds : sounds_)
    {
        Mix_FreeChunk(sounds.second);
    }
    sounds_.clear();

    for (auto &music : music_)
    {
        Mix_FreeMusic(music.second);
    }
    music_.clear();

    for (auto &font : fonts_)
    {
        TTF_CloseFont(font.second);
    }
    fonts_.clear();
}
