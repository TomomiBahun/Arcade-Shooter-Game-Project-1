#pragma once
#include "Task.h"
#include <vector>
#include <string>

class Conversation : public Task
{
public:
	Conversation();
	virtual ~Conversation() = default;
	bool update() override;
	void draw() const override;
	bool getBoss() { return _canBossCome; }

private:
	std::vector<const char*> reimuAndRan;
	std::vector<std::vector<int>> imageReimuAndRan;
	int _index;
	int _counter;
	bool _canBossCome;
};

