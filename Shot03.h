#pragma once
#include "AbstractShot.h"

class Shot03 : public AbstractShot
{
public:
	Shot03();
	virtual ~Shot03() = default;
	void setBullets(float x, float y, float angle, int power) override;

private:
	float _speed;
	int _bulletType;
	int _bulletColor;
	float _angle;
};
