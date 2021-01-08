#pragma once
#include "Task.h"
#include <vector>
#include <string>

class AbstractEndConversation : public Task
{
public:
	AbstractEndConversation() = default;
	virtual ~AbstractEndConversation() = default;
	virtual bool update() = 0;
	virtual void draw() const = 0;
	virtual int const getFlag() = 0;
};