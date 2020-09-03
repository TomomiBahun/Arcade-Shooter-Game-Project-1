#pragma once
#include "AbstractBoss.h"

class YakumoRan : public AbstractBoss
{
public:
	YakumoRan();
	virtual ~YakumoRan() = default;
	void draw() const override;
	bool update() override;

private:
	float angleBossAndPlayer();
	float angleBossAndDestination();
	void inputDestinationAndTime(int t, float xDest, float yDest);
	void moveBoss();
	void moveUpDown(); // stay at the base potision, but keep moving
};

