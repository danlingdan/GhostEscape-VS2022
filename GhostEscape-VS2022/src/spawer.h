#pragma once
#include "core/object.h"

class Player;
class Spawer : public Object
{
protected:
    int num_ = 10;
    float timer_ = 0.0f;
    float interval_ = 3.0f;

    Player *target_ = nullptr;

public:
    virtual void update(float dt) override;

    // getters and setters
    auto getNum() const { return num_; }
    void setNum(int num) { num_ = num; }
    auto getTimer() const { return timer_; }
    void setTimer(float timer) { timer_ = timer; }
    auto getInterval() const { return interval_; }
    void setInterval(float interval) { interval_ = interval; }
    auto getTarget() const { return target_; }
    void setTarget(Player *target) { target_ = target; }
};