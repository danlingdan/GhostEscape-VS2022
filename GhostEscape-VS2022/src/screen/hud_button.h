#pragma once

#include "../core/object_screen.h"
#include "../core/affiliate/sprite.h"

class HUDButton :public ObjectScreen
{
protected:
	Sprite* sprite_normal_ = nullptr;
	Sprite* sprite_hover_ = nullptr;
	Sprite* sprite_press_ = nullptr;

	bool is_hover_ = false;
	bool is_press_ = false;
	bool is_trigger_ = false;

public:
	static HUDButton* addHUDButtonChild(Object* parent, glm::vec2 render_pos,
		const std::string& file_path1, const std::string& file_path2,
		const std::string& file_path3, float scale = 1.0f,
		Anchor anchor = Anchor::CENTER);

	virtual void update(float dt) override;
	virtual bool handleEvents(SDL_Event& event) override;

	void checkHover();
	void checkState();

	// getter and setter
	auto getIsHover() const { return is_hover_; }
	auto getIsPress() const { return is_press_; }
	bool getIsTrigger();
	void setIsHover(bool hover) { is_hover_ = hover; }
	void setIsPress(bool press) { is_press_ = press; }
	void setIsTrigger(bool trigger) { is_trigger_ = trigger; }
	auto getSpriteNormal() const { return sprite_normal_; }
	auto getSpriteHover() const { return sprite_hover_; }
	auto getSpritePress() const { return sprite_press_; }
	void setScale(float scale);
	//void setSpriteNormal(Sprite* sprite) { sprite_normal_ = sprite; }
	//void setSpriteHover(Sprite* sprite) { sprite_hover_ = sprite; }
	//void setSpritePress(Sprite* sprite) { sprite_press_ = sprite; }
};