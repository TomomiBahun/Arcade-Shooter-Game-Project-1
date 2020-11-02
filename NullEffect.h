#pragma once
#include "Task.h"

class NullEffect : public Task
{
public:
	NullEffect() = default;
	virtual ~NullEffect() = default;
	bool update() override;
	void draw() const override;

	bool getEffectStatus() { return _isEffectOn; }

private:
	int _counter = 0;
	bool _isEffectOn = true;
};

