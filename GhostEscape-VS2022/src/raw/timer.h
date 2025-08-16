#pragma once

#include "../core/object.h"

class Timer :public Object
{
protected:
	float timer_ = 0.0f;
	float interval_ = 3.0f;
	bool time_out_ = false;

public:
	static Timer* addTimerChild(Object* parent, float interval = 3.0f);

	virtual void update(float dt) override;

	void start() { is_active_ = true; }
	bool timeOut();
	void stop() { is_active_ = false; }

	float getProgress() { return timer_ / interval_; }
	// getter and setter
	auto getTimer() const { return timer_; }
	auto getInterval() const { return interval_; }
	void setInterval(float interval) { interval_ = interval; }
	void setTimer(float timer) { timer_ = timer; }
};
