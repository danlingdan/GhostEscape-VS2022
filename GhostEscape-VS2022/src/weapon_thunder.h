#pragma once

#include "raw/weapon.h"

class WeaponThunder : public Weapon
{
public:
    static WeaponThunder *addWeaponThunderChild(Actor *parent, float cool_down = 0.5f, float mana_cost = 0.0f);
    virtual void handleEvents(SDL_Event &event) override;
};