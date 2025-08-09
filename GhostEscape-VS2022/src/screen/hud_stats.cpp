#include "hud_stats.h"
#include "../core/actor.h"
#include "../raw/stats.h"
#include "../core/affiliate/sprite.h"

HUDStats* HUDStats::addHUDStatsChild(Object* parent, Actor* target, glm::vec2 render_position)
{
	HUDStats* hud_stats = new HUDStats();
	hud_stats->init();
	hud_stats->setRenderPosition(render_position);
	hud_stats->setTarget(target);
	if (parent) parent->addChild(hud_stats);
	return hud_stats;
}

void HUDStats::init()
{
	ObjectScreen::init();

    // 获取屏幕尺寸
    glm::vec2 screen_size = game_.getScreenSize();

    // 计算比例位置和大小
    float bar_width = screen_size.x * 0.18f;
    float bar_height = screen_size.y * 0.04f;
    float bar_y = screen_size.y * 0.03f;
    float health_bar_x = screen_size.x * 0.02f;
    float mana_bar_x = screen_size.x * 0.22f;
    float icon_size = bar_height * 0.8f;

    // Health bar and icon
    health_bar_bg_ = Sprite::addSpriteChild(this, "assets/UI/bar_bg.png", bar_width / 100.0f, Anchor::CENTER_LEFT);
    health_bar_bg_->setOffset(glm::vec2(health_bar_x, bar_y));
    health_bar_ = Sprite::addSpriteChild(this, "assets/UI/bar_red.png", bar_width / 100.0f, Anchor::CENTER_LEFT);
    health_bar_->setOffset(glm::vec2(health_bar_x, bar_y));
    health_icon_ = Sprite::addSpriteChild(this, "assets/UI/Red Potion.png", icon_size / 50.0f, Anchor::CENTER_LEFT);
    health_icon_->setOffset(glm::vec2(health_bar_x - icon_size * 1.2f, bar_y - icon_size * 0.1f));

    // Mana bar and icon
    mana_bar_bg_ = Sprite::addSpriteChild(this, "assets/UI/bar_bg.png", bar_width / 100.0f, Anchor::CENTER_LEFT);
    mana_bar_bg_->setOffset(glm::vec2(mana_bar_x, bar_y));
    mana_bar_ = Sprite::addSpriteChild(this, "assets/UI/bar_blue.png", bar_width / 100.0f, Anchor::CENTER_LEFT);
    mana_bar_->setOffset(glm::vec2(mana_bar_x, bar_y));
    mana_icon_ = Sprite::addSpriteChild(this, "assets/UI/Blue Potion.png", icon_size / 50.0f, Anchor::CENTER_LEFT);
    mana_icon_->setOffset(glm::vec2(mana_bar_x - icon_size * 1.2f, bar_y - icon_size * 0.1f));

}

void HUDStats::update(float dt)
{
	ObjectScreen::update(dt);
	updateUIHealthBar();
	updateUIManaBar();
}

void HUDStats::updateUIHealthBar()
{
	if (!target_ || !health_bar_ || !target_->getStats()) return;
	health_bar_->setPercentage(glm::vec2(target_->getStats()->getHealth() / target_->getStats()->getMaxHealth(), 1.0f));
}

void HUDStats::updateUIManaBar()
{
	if (!target_ || !health_bar_ || !target_->getStats()) return;
	mana_bar_->setPercentage(glm::vec2(target_->getStats()->getMana() / target_->getStats()->getMaxMana(), 1.0f));
}
