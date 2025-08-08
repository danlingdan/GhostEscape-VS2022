#pragma once

#include "../core/object_world.h"
#include "../core/affiliate/sprite_anim.h"

class Spell : public ObjectWorld
{
protected:
    SpriteAnim *sprite_ = nullptr;
    float damage_ = 60.0f;

public:
    static Spell *addSpellChild(Object *parent, const std::string &file_path, glm::vec2 pos, float damage, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    virtual void update(float dt) override;

    // getter and setter
    inline SpriteAnim *getSprite() const { return sprite_; }
    inline void setSprite(SpriteAnim *sprite) { sprite_ = sprite; }
    inline float getDamage() const { return damage_; }
    inline void setDamage(float damage) { damage_ = damage; }

private:
    void attack();
};