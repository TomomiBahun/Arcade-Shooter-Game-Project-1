#pragma once
#include "AbstractBossShot.h"
#include "ImageBullet.h"

class RanShot03 : public AbstractBossShot
{
public:
	RanShot03();
	virtual ~RanShot03() = default;
	void setBullets(float x, float y, float angle, int power) override;

private:
	int _bulletType;
	float _speed01;
	float _speed02;
	int _bulletColor01;
	int _bulletColor02;
	int _randomNum;
	bool _leftRight; // false: LEFT, true:RIGHT
};