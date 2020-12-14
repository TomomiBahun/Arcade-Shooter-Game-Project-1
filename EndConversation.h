#pragma once
#include "Task.h"
#include <vector>
#include <string>

class EndConversation : public Task
{
public:
	EndConversation();
	virtual ~EndConversation() = default;
	bool update() override;
	void draw() const override;

private:
	std::vector<const char*> reimuAndRan;
	std::vector<std::vector<int>> imageReimuAndRan;
	int _index;
	int _counter;
};