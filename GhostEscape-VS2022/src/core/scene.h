#pragma once
#include "object.h"
#include "object_world.h"
#include <glm/glm.hpp>
#include <vector>

class Scene : public Object
{
protected:
    glm::vec2 camera_position_ = glm::vec2(0);

    glm::vec2 world_size_ = glm::vec2(0);

    std::vector<ObjectWorld *> children_world_;
    std::vector<ObjectScreen *> children__screen_;

    bool is_pause_ = false;
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init() override {}
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    // data save and load
    virtual void saveData(const std::string& file_path) {}
    virtual void loadData(const std::string& file_path) {}

    // getter and setter
    auto worldToScreen(const glm::vec2 &world_position) const { return world_position - camera_position_; }
    auto screenToWorld(const glm::vec2 &screen_position) const { return screen_position + camera_position_; }
    auto getCameraPosition() const { return camera_position_; }
    void setCameraPosition(const glm::vec2 &camera_position);
    auto getWorldSize() const { return world_size_; }
    void setWorldSize(const glm::vec2 &world_size) { world_size_ = world_size; }
    auto &getChildrenWorld() { return children_world_; }
    auto &getChildrenScreen() { return children__screen_; }
    auto getIsPause() const { return is_pause_; }
    void setIsPause(bool is_pause) { is_pause_ = is_pause; }

    virtual void addChild(Object *child) override;
    virtual void removeChild(Object *child) override;

    void pause();
    void resume();
};
