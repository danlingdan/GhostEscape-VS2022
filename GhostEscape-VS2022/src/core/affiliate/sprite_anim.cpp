#include "sprite_anim.h"

void SpriteAnim::update(float dt)
{

    if (is_finsh_)
    {
        return;
    }

    frame_timer_ += dt;
    if (frame_timer_ >= 1.0f / fps_)
    {
        current_frame_++;
        if (current_frame_ >= total_frame_)
        {
            current_frame_ = 0;

            if (!is_loop_)
            {
                is_finsh_ = true;
            }
        }
        frame_timer_ = 0.0f;
    }
    texture_.src_rect.x = texture_.src_rect.w * current_frame_;
}

SpriteAnim *SpriteAnim::addSpriteAnimChild(ObjectScreen *parent, const std::string &file_path, float scale, Anchor anchor)
{
    auto speite_anim = new SpriteAnim();
    speite_anim->init();
    speite_anim->setAnchor(anchor);
    speite_anim->setTexture(Texture(file_path));
    speite_anim->setScale(scale);
    speite_anim->setParent(parent);
    parent->addChild(speite_anim);
    return speite_anim;
}

void SpriteAnim::setTexture(const Texture &texture)
{
    texture_ = texture;
    total_frame_ = texture.src_rect.w / texture.src_rect.h;
    texture_.src_rect.w = texture_.src_rect.h;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
