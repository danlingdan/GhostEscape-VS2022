#pragma once
#include "game.h"
#include "defs.h"
#include <vector>
#include <algorithm>

class Object
{
protected:
    Game &game_ = Game::getInstance();

    ObjectType type_ = ObjectType::NONE;
    std::vector<Object *> children_;
    std::vector<Object *> object_to_add;

    bool is_active_ = true;
    bool need_remove_ = false;

public:
    Object() = default;
    virtual ~Object() = default;

    virtual void init() {}
    virtual bool handleEvents(SDL_Event &event);
    virtual void update(float dt);
    virtual void render();
    virtual void clean();

    virtual void addChild(Object *child) { children_.push_back(child); }
    virtual void removeChild(Object *child)
    {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
    }

    void safeAddChild(Object *child) { object_to_add.push_back(child); }

    // getter and setter
    auto getType() const { return type_; }
    void setType(ObjectType type) { type_ = type; }
    void setActive(bool active) { is_active_ = active; }
    auto getActive() const { return is_active_; }
    auto getNeedRemove() const { return need_remove_; }
    void setNeedRemove(bool need_remove) { need_remove_ = need_remove; }
};