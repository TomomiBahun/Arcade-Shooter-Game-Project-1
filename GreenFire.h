#pragma once
#include "AbstractEnemy.h"

class GreenFire final: public AbstractEnemy
{
public:
	GreenFire(float x, float y);
	~GreenFire() = default;
	void draw() const override;

protected:
	void setSize() override;
};

