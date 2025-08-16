#include "timer.h"

Timer* Timer::addTimerChild(Object* parent, float interval)
{
	auto timer = new Timer();
	timer->init();
	if (parent) { parent->addChild(timer); }
	timer->setActive(false);
	return timer;
}

void Timer::update(float dt)
{
	Object::update(dt);

	timer_ += dt;
	if (timer_ >= interval_)
	{
		timer_ = 0.0f;
		time_out_ = true;
	}
}

bool Timer::timeOut()
{
	if (time_out_)
	{
		time_out_ = false;
		return true;
	}
	else
	{
		return false;
	}
}
