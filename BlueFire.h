#pragma once
#include "AbstractEnemy.h"

class BlueFire final : public AbstractEnemy
{
public:
	BlueFire(float x, float y);
	~BlueFire() = default;
	bool update() override;
	void draw() const override;
	void shotDraw() const;
	float getX() const { return _x; }
	float getY() const { return _y; }

protected:
	void setSize() override;
	void setShot();
};

