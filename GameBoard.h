#pragma once
#include "Task.h"

class GameBoard final : public Task
{
public:
	GameBoard() = default;
	~GameBoard() = default;
	bool update() override;
	void draw() const override;
};

