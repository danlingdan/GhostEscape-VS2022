#pragma once
#include "../object_affiliate.h"
#include <string>

struct Texture
{
    SDL_Texture *texture = nullptr;
    SDL_FRect src_rect = {};
    float angle = 0.0f;
    bool is_flip = false;
    Texture() = default;
    Texture(const std::string &file_path);
};

class Sprite : public ObjectAffiliate
{
protected:
    Texture texture_;

    bool is_loop_ = true;
    bool is_finsh_ = false;

public:
    Sprite() = default;

    static Sprite *addSpriteChild(ObjectScreen *parent, const std::string &file_path, float scale = 1.0f, Anchor anchor = Anchor::NONE);

    virtual void render() override;

    // getter and setter
    auto getTexture() const { return texture_; }
    virtual void setTexture(const Texture &texture);
    auto getSize() const { return size_; }
    void setSize(const glm::vec2 &size) { size_ = size; }
    auto getOffset() const { return offset_; }
    void setOffset(const glm::vec2 &offset) { offset_ = offset; }
    auto getAngle() const { return texture_.angle; }
    void setAngle(float angle) { texture_.angle = angle; }
    auto isFlip() const { return texture_.is_flip; }
    void setFlip(bool flip) { texture_.is_flip = flip; }
    auto getIsLoop() const { return is_loop_; }
    auto getIsFinish() const { return is_finsh_; }
    void setIsLoop(bool loop) { is_loop_ = loop; }
    void setIsFinish(bool finish) { is_finsh_ = finish; }
};