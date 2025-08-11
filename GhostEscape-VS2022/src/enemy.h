#pragma once
#include "player.h"

class Enemy : public Actor
{
    Player *target_ = nullptr;

    enum class States
    {
        NORMAL,
        HURT,
        DIE
    };
    States current_state_ = States::NORMAL;

    SpriteAnim *anim_normal_ = nullptr;
    SpriteAnim *anim_hurt_ = nullptr;
    SpriteAnim *anim_die_ = nullptr;
    SpriteAnim *current_anim_ = nullptr;

    int score_ = 10;  // 击败敌人获得的分数

public:
    static Enemy *addEnemyChild(Object *parent, glm::vec2 pos, Player *target);
    virtual void init() override;
    virtual void update(float dt) override;

    void aim_target(Player *target);

    void checkStates();
    void changeStates(States new_state);

    void remove();

    void attack();

    // getter and setter
    auto getTarget() const { return target_; }
    void setTarget(Player *target) { target_ = target; }
};