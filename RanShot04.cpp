#include "RanShot04.h"
#include "Define.h"
#include <DxLib.h>
#include <math.h>

RanShot04::RanShot04() :
	_bulletType01(ImageBullet::sharpBullet), _bulletType02(ImageBullet::bigBall),
	_speed01(2.0), _speed02(8.0),
	_bulletColor01(ImageBullet::eAqua), _bulletColor02(ImageBullet::eBlue),
	_bulletColor03(ImageBullet::ePurple), _bulletColor04(ImageBullet::eRed),
	_baseShot(-1), _baseCounter(0)
{
	_angle = 0.0;
	_movePattern = 1;
}

/* this sets new bullets */
void RanShot04::setBullets(float x, float y, float angle, int power)
{
	int mod;
	if (_counter < 400) {
		mod = 100;
	}
	else {
		mod = 80;
	}

	/* find an available bullet */
	if (_counter % mod == 0) {
		int k = isBulletAvailable();
		shot[k].setFlag(1);
		shot[k].setBullet(x, y, _speed02, angle, power, _bulletType02, _bulletColor02);
		_baseShot = k;

	}

	if (shot[_baseShot].getY() > Define::CENTER_Y + 50 && _baseShot > -1) {
		makeFlower(shot[_baseShot].getX(), shot[_baseShot].getY(), angle, power, _bulletType01, _bulletColor01);
		_baseX = shot[_baseShot].getX();
		_baseY = shot[_baseShot].getY();
		shot[_baseShot].initBullet();
		_baseCounter = _counter;
		_baseShot = -1;
	}

	if (_counter < 400) {
		if (_baseCounter + 15 == _counter) {
			makeCircle(_baseX, _baseY, 60, angle, power, _bulletColor03, _bulletType01);
		}

		if (_baseCounter + 30 == _counter) {
			makeCircle(_baseX, _baseY, 120, angle, power, _bulletColor04, _bulletType01);
		}
	}
	else {
		if (_baseCounter + 15 == _counter) {
			makeBigCircle(_baseX, _baseY, 60, angle, power, _bulletColor03, _bulletType01);
		}

		if (_baseCounter + 30 == _counter) {
			makeBigCircle(_baseX, _baseY, 120, angle, power, _bulletColor04, _bulletType01);
		}
	}
}

void RanShot04::makeFlower(float x, float y, float angle, int power, int bulletColor, int bulletType)
{
	for (int i = 0; i < 4; i++) {
		int k = isBulletAvailable();
		shot[k].setFlag(1);
		shot[k].setBullet(x, y, _speed01, angle + (Define::PI/2) * i, power, bulletColor, bulletType);
	}
}

void RanShot04::makeCircle(float xs, float ys, int distance, float angle, int power, int bulletColor, int bulletType)
{
	int points = 8;
	double slice = angle + (2 * Define::PI) / points;
	for (int i = 0; i < points; i++) {
		double tempAngle = slice * i;
		int newX = (int)(xs + distance * cos(tempAngle));
		int newY = (int)(ys + distance * sin(tempAngle));
		makeFlower(newX, newY, tempAngle, power, bulletType, bulletColor);
	}
}

void RanShot04::makeBigCircle(float xs, float ys, int distance, float angle, int power, int bulletColor, int bulletType)
{
	int points = 16;
	double slice = angle + (2 * Define::PI) / points;
	for (int i = 0; i < points; i++) {
		double tempAngle = slice * i;
		int newX = (int)(xs + distance * cos(tempAngle));
		int newY = (int)(ys + distance * sin(tempAngle));
		makeFlower(newX, newY, tempAngle, power, bulletType, bulletColor);
	}
}