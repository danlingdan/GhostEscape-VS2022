#include "player.h"
#include "core/affiliate/sprite_anim.h"
#include "core/affiliate/coilder.h"
#include "raw/stats.h"
#include "core/affiliate/text_label.h"
#include "raw/timer.h"

void Player::init()
{
    Actor::init();

    flash_timer_ = Timer::addTimerChild(this, 0.4f);  // 创建一个周期为0.4秒的计时器
    flash_timer_->start();

    max_speed_ = 500.0f;
    sprite_idle_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-idle.png", 2.0);
    sprite_move_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-move.png", 2.0);
    sprite_move_->setActive(false);

    coilder_ = Coilder::addCoilderChild(this, sprite_idle_->getSize() / 2.0f);
    stats_ = Stats::addStatsChild(this);
    effect_ = Effect::addEffectChild(nullptr, "assets/effect/1764.png", glm::vec2(0), 2.0f, nullptr);
    weapon_thunder_ = WeaponThunder::addWeaponThunderChild(this, 1.0f, 20.0f);
}

bool Player::handleEvents(SDL_Event &event)
{
    if (Actor::handleEvents(event))
    {
        return true;
    }

    return false;
}

void Player::update(float dt)
{
    Actor::update(dt);
    keyboardControl();
    velocity_ *= 0.9f;
    checkStates();
    move(dt);
    syncCamera();
    checkIsDead();
}

void Player::render()
{
    if (stats_->getIsInvinsible() && flash_timer_->getProgress() < 0.5f) {
        return;  // 如果处于无敌状态且计时器进度小于50%，则不渲染（实现闪烁效果）
    }

    Actor::render();
}

void Player::clean()
{
    Actor::clean();
}

void Player::keyboardControl()
{
    auto currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W])
    {
        velocity_.y = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_S])
    {
        velocity_.y = max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_A])
    {
        velocity_.x = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_D])
    {
        velocity_.x = max_speed_;
    }
}

void Player::syncCamera()
{
    game_.getCurrentScene()->setCameraPosition(position_ - game_.getScreenSize() / 2.0f);
}

void Player::takeDamage(float damage)
{
    if (!stats_ || stats_->getIsInvinsible()) return;
    Actor::takeDamage(damage);
    game_.playSound("assets/sound/hit-flesh-02-266309.mp3");
}

void Player::checkStates()
{
    // is filp?
    if (velocity_.x < 0)
    {
        sprite_idle_->setFlip(true);
        sprite_move_->setFlip(true);
    }
    else
    {
        sprite_idle_->setFlip(false);
        sprite_move_->setFlip(false);
    }

    // idle or move
    bool new_is_moving = (glm::length(velocity_) > 0.1f);
    if (new_is_moving != is_moving_)
    {
        is_moving_ = new_is_moving;
        changStates(is_moving_);
    }
}

void Player::changStates(bool is_moving)
{
    if (is_moving)
    {
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        sprite_move_->setCurrentFrame(sprite_idle_->getCurrentFrame());
        sprite_move_->setFrameTimer(sprite_idle_->getFrameTimer());
    }
    else
    {
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurrentFrame(sprite_move_->getCurrentFrame());
        sprite_idle_->setFrameTimer(sprite_move_->getFrameTimer());
    }
}

void Player::checkIsDead()
{
    if (!stats_->getIsAlive())
    {
        game_.getCurrentScene()->safeAddChild(effect_);
        effect_->setPosition(getPosition());
        setActive(false);
        game_.playSound("assets/sound/female-scream-02-89290.mp3");
    }
}
