#pragma once
#include "AbstractEnemy.h"

class GreenFire01 final: public AbstractEnemy
{
public:
	GreenFire01(float x, float y);
	~GreenFire01() = default;
	bool update() override;
	void draw() const override;

protected:
	float index = 0.0;
	void setSize() override;
};

