#include "RanShot03.h"
#include "Define.h"
#include <DxLib.h>

RanShot03::RanShot03() : _bulletType(ImageBullet::sharpBullet),
_speed01(6.0), _speed02(2.0),
_bulletColor01(ImageBullet::eAqua), _bulletColor02(ImageBullet::ePurple),
_randomNum(0), _leftRight(false) // false: LEFT, true:RIGHT
{
	_angle = 0.0;
	_angle02 = 0.0;
	_movePattern = 2; // combination moveUp&Down and move to specific location
	_moveTime = 60;
	_moveX = Define::BOSSBASE_X;
	_moveY = Define::BOSSBASE_Y;
}

/* this sets new bullets */
void RanShot03::setBullets(float x, float y, float angle, int power)
{
	/* find an available bullet */
	if (_angle <= 2 * Define::PI) {
		_angle -= Define::PI / 360;
		_angle02 += Define::PI / 360;
	}
	if (_counter %10 == 0 && _counter > 60) {
		for (int i = 0; i < 8; i++) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed01, _angle + Define::PI / 2 - (Define::PI / 4 * i), power, _bulletType, _bulletColor01);
			int h = isBulletAvailable();
			shot[h].setFlag(1);
			shot[h].setBullet(x, y, _speed01, _angle02 + Define::PI / 2 - (Define::PI / 4 * i), power, _bulletType, _bulletColor01);
		}
	}

	if (_counter % 40 == 0 && _counter > 60) {
		for (int i = 0; i < 24; i++) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed02, angle + (Define::PI / 12 * i), power, _bulletType, _bulletColor02);
		}
	}
}