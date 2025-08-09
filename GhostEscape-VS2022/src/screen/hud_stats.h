#pragma once
#include "../core/object_screen.h"

class Actor;
class Sprite;
class HUDStats :public ObjectScreen
{
protected:
	Actor* target_ = nullptr;

	Sprite* health_bar_ = nullptr;
	Sprite* health_bar_bg_ = nullptr;
	Sprite* health_icon_ = nullptr;
	Sprite* mana_bar_ = nullptr;
	Sprite* mana_bar_bg_ = nullptr;
	Sprite* mana_icon_ = nullptr;

	float health_percentage_ = 1.0f;
	float mana_percentage_ = 1.0f;

public:
	static HUDStats* addHUDStatsChild(Object* parent, Actor* target, glm::vec2 render_position);
	virtual void init() override;
	virtual void update(float dt) override;


	// getter and setter
	void setTarget(Actor* target) { target_ = target; }
	auto getTarget() const { return target_; }
	void setHealthPercentage(float percentage) { health_percentage_ = percentage; }
	auto getHealthPercentage() const { return health_percentage_; }
	void setManaPercentage(float percentage) { mana_percentage_ = percentage; }
	auto getManaPercentage() const { return mana_percentage_; }
	auto getHealthBar() const { return health_bar_; }
	auto getHealthBarBg() const { return health_bar_bg_; }
	auto getHealthIcon() const { return health_icon_; }
	auto getManaBar() const { return mana_bar_; }
	auto getManaBarBg() const { return mana_bar_bg_; }
	auto getManaIcon() const { return mana_icon_; }
	void setHealthBar(Sprite* health_bar) { health_bar_ = health_bar; }
	void setHealthBarBg(Sprite* health_bar_bg) { health_bar_bg_ = health_bar_bg; }
	void setHealthIcon(Sprite* health_icon) { health_icon_ = health_icon; }
	void setManaBar(Sprite* mana_bar) { mana_bar_ = mana_bar; }
	void setManaBarBg(Sprite* mana_bar_bg) { mana_bar_bg_ = mana_bar_bg; }
	void setManaIcon(Sprite* mana_icon) { mana_icon_ = mana_icon; }

private:
	void updateUIHealthBar();
	void updateUIManaBar();
};

