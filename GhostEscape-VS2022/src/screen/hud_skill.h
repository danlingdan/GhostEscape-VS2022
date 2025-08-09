#pragma once
#include "../core/object_screen.h"

class Sprite;
class HUDSkill :public ObjectScreen 
{
protected:
	Sprite* icon_ = nullptr;
	float percentage_ = 1.0f;
public:
	static HUDSkill* addHUDSkillChild(Object* parent, const std::string& file_path, glm::vec2 pos, float scale = 1.0f, Anchor anchor = Anchor::CENTER);

	virtual void render() override;

	// getter and setter
	void setIcon(Sprite* icon) { icon_ = icon; }
	auto getIcon() const { return icon_; }
	void setPercentage(float percentage);
	auto getPercentage() const { return percentage_; }
};
