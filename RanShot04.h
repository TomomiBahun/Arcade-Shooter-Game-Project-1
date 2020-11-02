#pragma once
#include "AbstractBossShot.h"
#include "ImageBullet.h"

class RanShot04 : public AbstractBossShot
{
public:
	RanShot04();
	virtual ~RanShot04() = default;
	void setBullets(float x, float y, float angle, int power) override;

private:
	int _bulletType01;
	int _bulletType02;
	float _speed01;
	float _speed02;
	int _bulletColor01;
	int _bulletColor02;
	int _bulletColor03;
	int _bulletColor04;
	float _angle;
	int _baseShot;
	int _baseCounter;
	float _baseX;
	float _baseY;
	//float _baseAngle;

	void makeFlower(float x, float y, float angle, int power, int bulletColor, int bulletType);
	void makeCircle(float xs, float ys, int distance, float angle, int power, int bulletColor, int bulletType);
	void makeBigCircle(float xs, float ys, int distance, float angle, int power, int bulletColor, int bulletType);
};