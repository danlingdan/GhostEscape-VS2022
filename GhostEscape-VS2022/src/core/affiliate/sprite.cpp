#include "sprite.h"

Sprite *Sprite::addSpriteChild(ObjectScreen *parent, const std::string &file_path, float scale, Anchor anchor)
{
    auto speite = new Sprite();
    speite->init();
    speite->setTexture(Texture(file_path));
    speite->setScale(scale);
    speite->setParent(parent);
    parent->addChild(speite);
    return speite;
}

void Sprite::render()
{
    if (!texture_.texture || !parent_ || is_finsh_)
    {
        return;
    }

    auto pos = parent_->getRenderPosition() + offset_;
    game_.renderTexture(texture_, pos, size_);
}

void Sprite::setTexture(const Texture &texture)
{
    texture_ = texture;
    size_ = glm::vec2(texture.src_rect.w, texture.src_rect.h);
}

Texture::Texture(const std::string &file_path)
{
    texture = Game::getInstance().getAssetStore()->getImage(file_path);
    if (texture)
    {
        SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
        src_rect.x = 0;
        src_rect.y = 0;
    }
}
