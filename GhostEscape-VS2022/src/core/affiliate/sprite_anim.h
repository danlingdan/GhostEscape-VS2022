#pragma once
#include "sprite.h"

class SpriteAnim : public Sprite
{
    int current_frame_ = 0;
    int total_frame_ = 0;
    int fps_ = 10;
    float frame_timer_ = 0.0f;

public:
    virtual void update(float dt) override;

    static SpriteAnim *addSpriteAnimChild(ObjectScreen *parent, const std::string &file_path, float scale = 1.0f, Anchor anchor = Anchor::CENTER);

    // getter and settet
    auto getCurrentFrame() const { return current_frame_; }
    auto getTotalFrame() const { return total_frame_; }
    auto getFps() const { return fps_; }
    auto getFrameTimer() const { return frame_timer_; }

    // setter
    void setCurrentFrame(int frame) { current_frame_ = frame; }
    void setTotalFrame(int frame) { total_frame_ = frame; }
    void setFps(int fps) { fps_ = fps; }
    void setFrameTimer(float timer) { frame_timer_ = timer; }
    virtual void setTexture(const Texture &texture) override;
};