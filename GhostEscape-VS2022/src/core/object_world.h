#pragma once
#include "object_screen.h"
#include "affiliate/coilder.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_ = glm::vec2(0, 0);
    Coilder *coilder_ = nullptr;

public:
    virtual void init() override { type_ = ObjectType::OBJECT_WORLD; }
    virtual void update(float dt) override;

    virtual void takeDamage(float damage) { (void)damage; }
    // getter and setter
    virtual glm::vec2 getPosition() const override { return position_; }
    void setPosition(const glm::vec2 &position);
    virtual void setRenderPosition(const glm::vec2 &render_position) override;
    auto getCoilder() const { return coilder_; }
    void setCoilder(Coilder *coilder) { coilder_ = coilder; }
};