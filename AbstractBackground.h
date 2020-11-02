#pragma once
#include "Task.h"

class AbstractBackground : public Task
{
public:
	AbstractBackground() = default;
	virtual ~AbstractBackground() = default;
	void setBossBackStatus(bool bossBackStatus) { bossBackOn = bossBackStatus; }
	bool bossBackOn = false;
};

