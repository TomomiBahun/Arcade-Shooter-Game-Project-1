#pragma once
#include "AbstractEnemy.h"

class GreenFire02 final : public AbstractEnemy
{
public:
	GreenFire02(float x, float y);
	~GreenFire02() = default;
	bool update() override;
	void draw() const override;

protected:
	void setSize() override;
};

