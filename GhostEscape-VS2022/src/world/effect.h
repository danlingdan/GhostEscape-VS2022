#pragma once
#include "../core/object_world.h"
#include "../core/affiliate/sprite_anim.h"
#include <string>

class Effect : public ObjectWorld
{
    SpriteAnim *sprite_ = nullptr;
    ObjectWorld *next_object_ = nullptr; // add object after playing

public:
    static Effect *addEffectChild(Object *parent, const std::string &file_path, glm::vec2 pos, float scale = 1.0f, ObjectWorld *next_object = nullptr);
    virtual void update(float dt) override;

    // getter and setter
    SpriteAnim *getSprite() const { return sprite_; }
    void setSprite(SpriteAnim *sprite) { sprite_ = sprite; }
    ObjectWorld *getNextObject() const { return next_object_; }
    void setNextObject(ObjectWorld *next_object) { next_object_ = next_object; }

private:
    void checkFinsh();
};