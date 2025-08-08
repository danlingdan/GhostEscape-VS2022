#include "../core/actor.h"

class Stats : public Object
{
protected:
    Actor *parent_ = nullptr;
    float health_ = 100.0f;
    float max_health_ = 100.0f;
    float mana_ = 100.0f;
    float max_mana_ = 100.0f;
    float damage_ = 40.0f;
    float mana_regen_ = 10.0f;

    float invinsible_timer_ = 0.0f;
    float invinsible_time_ = 1.5f;
    bool is_alive_ = true;
    bool is_invinsible_ = false;

public:
    static Stats *addStatsChild(Actor *parent, float max_health = 100.0f, float max_mana = 100.0f, float damage = 40.0f, float mana_regen = 10.0f);

    virtual void update(float dt) override;
    bool canUseMana(float mana_cost);
    void useMana(float mana_cost);
    void regenMana(float dt);
    void takeDamage(float damage);

    // getter and setter
    auto getParent() const { return parent_; }
    void setParent(Actor *parent) { parent_ = parent; }
    auto getHealth() const { return health_; }
    void setHealth(float health) { health_ = health; }
    auto getMaxHealth() const { return max_health_; }
    void setMaxHealth(float max_health) { max_health_ = max_health; }
    auto getMana() const { return mana_; }
    void setMana(float mana) { mana_ = mana; }
    auto getMaxMana() const { return max_mana_; }
    void setMaxMana(float max_mana) { max_mana_ = max_mana; }
    auto getDamage() const { return damage_; }
    void setDamage(float damage) { damage_ = damage; }
    auto getManaRegen() const { return mana_regen_; }
    void setManaRegen(float mana_regen) { mana_regen_ = mana_regen; }
    auto getIsAlive() const { return is_alive_; }
    void setIsAlive(bool is_alive) { is_alive_ = is_alive; }
    auto getIsInvinsible() const { return is_invinsible_; }
    void setIsInvinsible(bool is_invinsible) { is_invinsible_ = is_invinsible; }
    auto getInvinsibleTimer() const { return invinsible_timer_; }
    void setInvinsibleTimer(float timer) { invinsible_timer_ = timer; }
    auto getInvinsibleTime() const { return invinsible_time_; }
    void setInvinsibleTime(float time) { invinsible_time_ = time; }
};