#pragma once
#include "AbstractBoss.h"
#include "AbstractBossShot.h"

class YakumoRan : public AbstractBoss
{
public:
	YakumoRan();
	virtual ~YakumoRan() = default;
	void draw() const override;
	bool update() override;
	bool updateShot(int movePattern, float x, float y);

private:
	bool preShot;
	bool isReadyForEffect;
	bool isShot01Ready;
	bool isShot02Ready;
};

