#pragma once
#include "Task.h"
class AbstractConversation : public Task
{
public:
	AbstractConversation() = default;
	virtual ~AbstractConversation() = default;
	virtual bool update() = 0;
	virtual void draw() const = 0;
	virtual bool getBoss() = 0;

protected:

};

