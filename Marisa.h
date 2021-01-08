#pragma once
#include "Player.h"
class Marisa : public Player
{
public:
	Marisa(int speed, int power, float range);
	virtual ~Marisa() = default;
	void draw() const override;
	void move() override;
};

