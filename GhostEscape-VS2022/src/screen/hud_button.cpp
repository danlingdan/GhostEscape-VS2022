#include "hud_button.h"

HUDButton* HUDButton::addHUDButtonChild(Object* parent, glm::vec2 render_pos, const std::string& file_path1, const std::string& file_path2, const std::string& file_path3, float scale, Anchor anchor)
{
	auto hud_button = new HUDButton();
	hud_button->init();
	hud_button->setRenderPosition(render_pos);

	// create 3 kinds of sprites
	hud_button->sprite_normal_ = Sprite::addSpriteChild(hud_button, file_path1, scale, anchor);
	hud_button->sprite_hover_ = Sprite::addSpriteChild(hud_button, file_path2, scale, anchor);
	hud_button->sprite_press_ = Sprite::addSpriteChild(hud_button, file_path3, scale, anchor);

	// only normal is active when initializing.
	hud_button->sprite_hover_->setActive(false);
	hud_button->sprite_press_->setActive(false);

	if (parent) parent->addChild(hud_button);
	return hud_button;
}

void HUDButton::update(float dt)
{
	ObjectScreen::update(dt);

	checkHover();
	checkState();
}

bool HUDButton::handleEvents(SDL_Event& event)
{
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
	{
		if (event.button.button == SDL_BUTTON_LEFT) 
		{
			if (is_hover_) 
			{  
				is_press_ = true;
				game_.playSound("assets/sound/UI_button08.wav");
				return true;
			}
		}
	}
	else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) 
	{
		if (event.button.button == SDL_BUTTON_LEFT) 
		{
			is_press_ = false;
			if (is_hover_) 
			{  // 只有当鼠标悬停在按钮上放开时，才触发按钮
				is_trigger_ = true;
				return true;
			}
		}
	}

	return false;
}

void HUDButton::checkHover()
{
	bool new_hover_;

	auto pos = render_position_ + sprite_normal_->getOffset();
	auto size = sprite_normal_->getSize();

	if (game_.isMouseRect(pos, pos + size))
	{
		new_hover_ = true;
	}
	else
	{
		new_hover_ = false;
	}

	if (new_hover_ != is_hover_)
	{
		is_hover_ = new_hover_;
		if (is_hover_ && !is_press_)
		{
			game_.playSound("assets/sound/UI_button12.wav");
		}
	}
}

void HUDButton::checkState()
{
	if (!is_press_ && !is_hover_)
	{
		sprite_normal_->setActive(true);
		sprite_hover_->setActive(false);
		sprite_press_->setActive(false);
	}
	else if (!is_press_ && is_hover_)
	{
		sprite_normal_->setActive(false);
		sprite_hover_->setActive(true);
		sprite_press_->setActive(false);
	}
	else
	{
		sprite_normal_->setActive(false);
		sprite_hover_->setActive(false);
		sprite_press_->setActive(true);
	}
}

bool HUDButton::getIsTrigger()
{
	if (is_trigger_ == true)
	{
		is_trigger_ = false;
		return true;
	}
	else
	{
		return false;
	}
}

void HUDButton::setScale(float scale)
{
	sprite_normal_->setScale(scale);
	sprite_hover_->setScale(scale);
	sprite_press_->setScale(scale);
}
