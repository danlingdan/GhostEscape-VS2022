#pragma once
#include "object.h"

class ObjectScreen : public Object
{
protected:
    glm::vec2 render_position_ = glm::vec2(0, 0);

public:
    ObjectScreen() = default;
    virtual ~ObjectScreen() = default;

    virtual void init() override { type_ = ObjectType::OBJECT_SCREEN; };

    // getter and setter
    auto getRenderPosition() const { return render_position_; }
    virtual void setRenderPosition(const glm::vec2 &render_position) { render_position_ = render_position; }
    virtual glm::vec2 getPosition() const { return glm::vec2(0); }
};
