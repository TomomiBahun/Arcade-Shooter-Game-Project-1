#pragma once
#include "AbstractBoss.h"
#include "AbstractBossShot.h"
#include "SpellCardEffect.h"

class YakumoRan : public AbstractBoss
{
public:
	YakumoRan();
	virtual ~YakumoRan() = default;
	void draw() const override;
	bool update() override;
	bool updateShot();

private:
	//bool preShot;
	bool isReadyForEffect;
	bool isShot01Ready;
	bool isShot02Ready;
	std::vector<std::vector<int>> _healthRange; // holds upper limit and lower limit of health when boss is at specific bullet
	SpellCardEffect effect;
};

