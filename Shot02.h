#pragma once
#include "AbstractShot.h"

class Shot02 : public AbstractShot
{
public:
	Shot02();
	virtual ~Shot02() = default;
	void setBullets(float x, float y, float angle, int power) override;

private:
	float _speed;
	int _bulletType;
	int _bulletColor;
};
