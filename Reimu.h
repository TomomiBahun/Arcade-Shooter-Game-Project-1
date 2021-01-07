#pragma once
#include "Player.h"

class Reimu : public Player
{
public:
	Reimu(int speed, int power, float range);
	virtual ~Reimu() = default;
	void draw() const override;
	void move() override;
};

