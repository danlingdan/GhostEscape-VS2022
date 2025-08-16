#pragma once
#include "core/actor.h"
#include "core/scene.h"
#include "core/affiliate/sprite_anim.h"
#include "world/effect.h"
#include "weapon_thunder.h"

class Timer;
class Player : public Actor
{
protected:
    SpriteAnim *sprite_idle_ = nullptr;
    SpriteAnim *sprite_move_ = nullptr;
    bool is_moving_ = false;

    Effect *effect_ = nullptr;

    WeaponThunder *weapon_thunder_ = nullptr;

    Timer* flash_timer_ = nullptr;
public:
    virtual void init() override;
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void keyboardControl();

    void syncCamera();

    virtual void takeDamage(float damage) override;

    void checkStates();
    void changStates(bool);

    void checkIsDead();
};