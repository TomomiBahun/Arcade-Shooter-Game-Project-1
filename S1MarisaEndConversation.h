#pragma once
#include "AbstractEndConversation.h"
#include <vector>
#include <string>

class S1MarisaEndConversation : public AbstractEndConversation
{
public:
	S1MarisaEndConversation();
	virtual ~S1MarisaEndConversation() = default;
	bool update() override;
	void draw() const override;
	int const getFlag() { return _flag; }

private:
	std::vector<const char*> marisaAndRan;
	std::vector<std::vector<int>> imageMarisaAndRan;
	int _index;
	int _counter;
	bool _flag; // when the flag is true, the conversation is done
};