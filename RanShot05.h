#pragma once
#include "AbstractBossShot.h"
#include "ImageBullet.h"

class RanShot05 : public AbstractBossShot
{
public:
	RanShot05();
	virtual ~RanShot05() = default;
	void setBullets(float x, float y, float angle, int power) override;

private:
	int _bulletType;
	float _speed01;
	float _speed02;
	int _bulletColor01;
	int _bulletColor02;
	float _angle;
	int _randomNum;
};