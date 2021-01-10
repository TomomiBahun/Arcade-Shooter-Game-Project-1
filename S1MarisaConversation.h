#pragma once
#include "AbstractConversation.h"
#include <vector>
#include <string>

class S1MarisaConversation : public AbstractConversation
{
public:
	S1MarisaConversation();
	virtual ~S1MarisaConversation() = default;
	bool update() override;
	void draw() const override;
	bool getBoss() { return _canBossCome; }

private:
	std::vector<const char*> marisaAndRan;
	std::vector<std::vector<int>> imageMarisaAndRan;
	int _index;
	int _counter;
	bool _canBossCome;
};
