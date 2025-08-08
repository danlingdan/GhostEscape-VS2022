#pragma once
#include "object_world.h"

class AffiliateBar;
class Stats;
class Actor : public ObjectWorld
{
protected:
    Stats *stats_ = nullptr;
    glm::vec2 velocity_ = glm::vec2(0, 0);
    float max_speed_ = 100.0f;

    AffiliateBar *health_bar_ = nullptr;

public:
    virtual void update(float dt) override;
    virtual void move(float dt);

    virtual void takeDamage(float damage) override;
    bool isAlive();

    void updateHealthBar();
    // getter and setter
    auto getStats() const { return stats_; }
    void setStats(Stats *stats) { stats_ = stats; }
    auto getVelocity() const { return velocity_; }
    auto getMaxSpeed() const { return max_speed_; }
    void setVelocity(const glm::vec2 &velocity) { velocity_ = velocity; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
    void setHealthBar(AffiliateBar *health_bar) { health_bar_ = health_bar; }
    auto getHealthBar() const { return health_bar_; }
};