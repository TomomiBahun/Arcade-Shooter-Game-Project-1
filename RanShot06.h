#pragma once
#include "AbstractBossShot.h"
#include "ImageBullet.h"

class RanShot06 : public AbstractBossShot
{
public:
	RanShot06();
	virtual ~RanShot06() = default;
	void setBullets(float x, float y, float angle, int power) override;

private:
	void setCircleBullets(float x, float y, int power, double decreaseSpeedRate);

	int _bulletType1;
	int _bulletType2;
	int _bulletType3;
	float _speed01;
	float _speed02;
	int _bulletColor01;
	int _bulletColor02;
	float _angle;
	int _baseCounter;
	int _baseCounter2;
	int _hideCounter;
	int _appearCounter;
	int _soundCounter;
	double _bulletX;
	double _bulletY;
};
