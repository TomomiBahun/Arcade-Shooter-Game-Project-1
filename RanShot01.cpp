#include "RanShot01.h"
#include "Define.h"
#include <DxLib.h>

RanShot01::RanShot01() : _bulletType(ImageBullet::sharpBullet),
	_speed01(7.0), _speed02(2.0),
	_bulletColor01(ImageBullet::eAqua), _bulletColor02(ImageBullet::ePurple),
	_randomNum(0), _leftRight(false) // false: LEFT, true:RIGHT
{
	_angle = 0.0;
	_movePattern = 1; // combination moveUp&Down and move to specific location
	_moveTime = 100;
	_moveX = Define::BOSSBASE_X;
	_moveY = Define::BOSSBASE_Y;
}

/* this sets new bullets */
void RanShot01::setBullets(float x, float y, float angle, int power)
{
	/* find an available bullet */
	if (_angle <= 2 * Define::PI) {
		_angle -= Define::PI / 360;
	}
	if (_counter % 10 == 0 && _counter != 0) {
		for (int i = 0; i < 8; i++) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed01, _angle + Define::PI / 2 - (Define::PI / 4 * i), power, _bulletType, _bulletColor01);
		}
	}

	if (_counter % 30 == 0 && _counter != 0) {
		for (int i = 0; i < 24; i++) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed02, angle + (Define::PI / 12 * i), power, _bulletType, _bulletColor02);
		}
	}

	// if counter becomes over 360, reset it
	if (_counter == 360) {
		_counter = 0;
	}

	if (_counter % (_moveTime * 2) == 0) {
		_randomNum = GetRand(10);

		if (Define::BOSSBASE_X - 200 < x < Define::BOSSBASE_X + 200) {
			if (_randomNum > 5) {
				_moveX -= (100.0+ (float)_randomNum*10);
			}
			else {
				_moveX += (100.0 + (float)_randomNum * 10);
			}
		}
		else if (x < Define::BOSSBASE_X) {
			_moveX += 100.0;
		}
		else if (Define::BOSSBASE_X < x) {
			_moveX -= 100.0;
		}
	}
}