#include "stats.h"

Stats *Stats::addStatsChild(Actor *parent, float max_health, float max_mana, float damage, float mana_regen)
{
    Stats *stats = new Stats();
    stats->init();
    stats->setParent(parent);
    stats->setMaxHealth(max_health);
    stats->setHealth(max_health);
    stats->setMaxMana(max_mana);
    stats->setMana(max_mana);
    stats->setDamage(damage);
    stats->setManaRegen(mana_regen);
    parent->addChild(stats);
    return stats;
}

void Stats::update(float dt)
{
    Object::update(dt);
    regenMana(dt);
    if (is_invinsible_)
    {
        invinsible_timer_ += dt;
        if (invinsible_timer_ >= invinsible_time_)
        {
            is_invinsible_ = false;
            invinsible_timer_ = 0.0f;
        }
    }
}

bool Stats::canUseMana(float mana_cost)
{
    return mana_ >= mana_cost;
}

void Stats::useMana(float mana_cost)
{
    mana_ -= mana_cost;
    if (mana_ < 0)
    {
        mana_ = 0;
    }
}

void Stats::regenMana(float dt)
{
    mana_ += mana_regen_ * dt;
    if (mana_ >= max_mana_)
    {
        mana_ = max_mana_;
    }
}

void Stats::takeDamage(float damage)
{
    if (is_invinsible_)
    {
        return;
    }
    health_ -= damage;

    if (health_ <= 0)
    {
        health_ = 0;
        is_alive_ = false;
    }
    // SDL_Log("health%f", health_);
    is_invinsible_ = true;
    invinsible_timer_ = 0.0f;
}
