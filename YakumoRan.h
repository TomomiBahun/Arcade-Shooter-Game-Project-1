#pragma once
#include "AbstractBoss.h"
#include "AbstractBossShot.h"
#include "SpellCardEffect.h"
#include "NullEffect.h"
#include "BossDefeatEffect.h"

class YakumoRan : public AbstractBoss
{
public:
	YakumoRan();
	virtual ~YakumoRan() = default;
	void draw() const override;
	bool update() override;
	bool updateShot();
	bool getShouldRanHide() { return shouldRanHide; }

private:
	bool isReadyForEffect;
	bool shouldRanHide; // switch to hide Ran's image for spellCard6 and the end of the stage
	std::vector<std::vector<int>> _healthRange; // holds upper limit and lower limit of health when boss is at specific bullet
	SpellCardEffect effect;
	NullEffect nullEffect;
	BossDefeatEffect bossDefeatEffect;
};

