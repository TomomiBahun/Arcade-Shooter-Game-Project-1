#pragma once
#include "AbstractEndConversation.h"
#include <vector>
#include <string>

class S1ReimuEndConversation : public AbstractEndConversation
{
public:
	S1ReimuEndConversation();
	virtual ~S1ReimuEndConversation() = default;
	bool update() override;
	void draw() const override;
	int const getFlag() { return _flag; }

private:
	std::vector<const char*> reimuAndRan;
	std::vector<std::vector<int>> imageReimuAndRan;
	int _index;
	int _counter;
	bool _flag; // when the flag is true, the conversation is done
};