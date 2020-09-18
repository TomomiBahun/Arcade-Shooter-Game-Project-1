#pragma once
#include "AbstractBossShot.h"
#include "ImageBullet.h"

class RanShot01 : public AbstractBossShot
{
public:
	RanShot01();
	virtual ~RanShot01() = default;
	void setBullets(float x, float y, float angle, int power) override;

private:
	int _bulletType;
	float _speed01;
	float _speed02;
	int _bulletColor01;
	int _bulletColor02;
};

