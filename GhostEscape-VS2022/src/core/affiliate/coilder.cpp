#include "coilder.h"

void Coilder::render()
{
#ifdef DEBUG_MODE
    auto pos = parent_->getRenderPosition() + offset_;
    game_.renderFillCircle(pos, size_, 0.3);
#endif
}

bool Coilder::isCoilding(Coilder *other)
{
    if (other == nullptr)
    {
        return false;
    }
    if (type_ == Type::CIRCLE && other->type_ == Type::CIRCLE)
    {
        auto point1 = parent_->getPosition() + offset_ + size_ / 2.0f;
        auto point2 = other->parent_->getPosition() + other->offset_ + other->size_ / 2.0f;
        return (glm::length(point1 - point2) < (size_.x + other->size_.x) / 2.0f);
    }
    return false;
}

Coilder *Coilder::addCoilderChild(ObjectScreen *parent, glm::vec2 size, Type type, Anchor anchor)
{
    auto coilder = new Coilder();
    coilder->init();
    coilder->setParent(parent);
    coilder->setSize(size);
    coilder->setAnchor(anchor);
    coilder->setType(type);
    parent->addChild(coilder);
    return coilder;
}
