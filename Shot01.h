#pragma once
#include "AbstractShot.h"

class Shot01 : public AbstractShot
{
public:
	Shot01();
	virtual ~Shot01() = default;
	void setBullets(float x, float y, float angle, int power) override;

private:
	float _speed;
	int _bulletType;
	int _bulletColor;
};

