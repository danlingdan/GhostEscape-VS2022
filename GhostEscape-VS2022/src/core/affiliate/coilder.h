#pragma once

#include "../object_affiliate.h"

class Spell;
class Coilder : public ObjectAffiliate
{
protected:
    friend Spell;
    enum class Type
    {
        RECTANGLE,
        CIRCLE // size.x=2r=d,default x=y
    };
    Type type_ = Type::CIRCLE;

public:
    virtual void render() override;

    bool isCoilding(Coilder *other);

    static Coilder *addCoilderChild(ObjectScreen *parent, glm::vec2 size, Type type = Type::CIRCLE, Anchor anchor = Anchor::NONE);

    // getter and setter
    auto getType() const { return type_; }
    void setType(Type type) { type_ = type; }
};