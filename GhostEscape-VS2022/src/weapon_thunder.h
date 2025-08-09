#pragma once

#include "raw/weapon.h"
#include "screen/hud_skill.h"

class WeaponThunder : public Weapon
{
protected:
    HUDSkill* hud_skill_ = nullptr;
public:
    static WeaponThunder *addWeaponThunderChild(Actor *parent, float cool_down = 0.5f, float mana_cost = 0.0f);
    virtual void init() override;
    virtual void update(float dt) override;
    virtual void handleEvents(SDL_Event &event) override;
};