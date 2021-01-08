#pragma once
#include "AbstractConversation.h"
#include <vector>
#include <string>

class S1ReimuConversation : public AbstractConversation
{
public:
	S1ReimuConversation();
	virtual ~S1ReimuConversation() = default;
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

