#include "enemy.h"
#include "core/affiliate/sprite_anim.h"
#include "raw/stats.h"
#include "core/affiliate/affiliate_bar.h"

Enemy *Enemy::addEnemyChild(Object *parent, glm::vec2 pos, Player *target)
{
    auto enemy = new Enemy();
    enemy->init();
    enemy->setPosition(pos);
    enemy->setTarget(target);
    if (parent)
        parent->addChild(enemy);
    return enemy;
}

void Enemy::init()
{
    Actor::init();
    anim_normal_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
    anim_hurt_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
    anim_die_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
    anim_hurt_->setActive(false);
    anim_die_->setActive(false);
    anim_die_->setIsLoop(false);

    current_anim_ = anim_normal_;
    coilder_ = Coilder::addCoilderChild(this, anim_normal_->getSize());
    stats_ = Stats::addStatsChild(this);

    auto size = anim_normal_->getSize();
    health_bar_ = AffiliateBar::addAffiliateBarChild(this, glm::vec2(size.x - 10, 10), Anchor::BOTTOM_CENTER);
    health_bar_->setOffset(health_bar_->getOffset() + glm::vec2(0, size.y / 2.0f - 5.0f));

    setType(ObjectType::ENEMY);
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    if (target_->getActive())
    {
        aim_target(target_);
        move(dt);
        attack();
    }
    checkStates();
    remove();
}

void Enemy::aim_target(Player *target)
{
    if (target == nullptr)
        return;
    auto direction = target->getPosition() - this->getPosition();
    direction = glm::normalize(direction);
    velocity_ = direction * max_speed_;
}

void Enemy::checkStates()
{
    States new_state;
    if (stats_->getHealth() <= 0)
    {
        new_state = States::DIE;
    }
    else if (stats_->getIsInvinsible())
    {
        new_state = States::HURT;
    }
    else
    {
        new_state = States::NORMAL;
    }

    if (new_state != current_state_)
    {
        changeStates(new_state);
    }
}

void Enemy::changeStates(States new_state)
{
    current_anim_->setActive(false);
    switch (new_state)
    {
    case States::NORMAL:
        current_anim_ = anim_normal_;
        current_anim_->setActive(true);
        break;
    case States::HURT:
        current_anim_ = anim_hurt_;
        current_anim_->setActive(true);
        break;
    case States::DIE:
        current_anim_ = anim_die_;
        current_anim_->setActive(true);
        game_.addScore(score_);
        break;
    }

    current_state_ = new_state;
}

void Enemy::remove()
{
    if (anim_die_->getIsFinish())
    {
        need_remove_ = true;
    }
}

void Enemy::attack()
{
    if (!coilder_ || !target_ || target_->getCoilder() == nullptr)
    {
        return;
    }

    if (coilder_->isCoilding(target_->getCoilder()))
    {
        if (stats_ && target_->getStats())
        {
            target_->takeDamage(stats_->getDamage());
        }
        // SDL_Log("Coilder!");
    }
}
