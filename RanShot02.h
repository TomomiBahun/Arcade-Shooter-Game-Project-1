#pragma once
#include "AbstractBossShot.h"
#include "ImageBullet.h"

class RanShot02 : public AbstractBossShot
{
public:
	RanShot02();
	virtual ~RanShot02() = default;
	void setBullets(float x, float y, float angle, int power) override;

private:
	int _bulletType01;
	int _bulletType02;
	int _bulletType03;
	int _bulletType04;
	float _speed01;
	float _speed02;
	float _speed03;
	float _speed04;
	int _bulletColor01;
	int _bulletColor02;
	int _bulletColor03;
	int _bulletColor04;
	bool _bulletSwitch;
	float _angle;
};

