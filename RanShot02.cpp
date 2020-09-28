#include "RanShot02.h"
#include "Define.h"
#include <DxLib.h>

RanShot02::RanShot02() :
	_bulletType01(ImageBullet::sharpBullet), _bulletType02(ImageBullet::bigBall),
	_bulletType03(ImageBullet::bigBall), _bulletType04(ImageBullet::bigBall),
	_speed01(9.0), _speed02(4.0),
	_speed03(7.0), _speed04(4.0),
	_bulletColor01(ImageBullet::eAqua), _bulletColor02(ImageBullet::eBlue),
	_bulletColor03(ImageBullet::eRed), _bulletColor04(ImageBullet::eOrange),
	_bulletSwitch(false)
{
	_angle = 0.0;
	_movePattern = 2;
	_moveX = Define::CENTER_X;
	_moveY = Define::CENTER_Y;
	_moveTime = 30;
}

/* this sets new bullets */
void RanShot02::setBullets(float x, float y, float angle, int power)
{
	/* find an available bullet */
	if (!_bulletSwitch) {
		if (_angle <= 2 * Define::PI) {
			_angle += Define::PI / 360;
		}
		if (_counter % 3 == 0 && _counter > _moveTime) {
			for (int i = 0; i < 4; i++) {
				int k = isBulletAvailable();
				shot[k].setFlag(1);
				shot[k].setBullet(x - 5.0, y, _speed01, _angle + Define::PI / 2 + (Define::PI / 2 * i), power, _bulletType01, _bulletColor01);
			}
			for (int i = 0; i < 4; i++) {
				int h = isBulletAvailable();
				shot[h].setFlag(1);
				shot[h].setBullet(x + 5.0, y, _speed01, _angle + Define::PI / 2 + (Define::PI / 2 * i) + 0.5, power, _bulletType01, _bulletColor01);
			}
		}


		if (_counter % 15 == 0 && _counter > _moveTime) {
			for (int i = 0; i < 4; i++) {
				int k = isBulletAvailable();
				shot[k].setFlag(1);
				shot[k].setBullet(x - 8.0, y, _speed02, angle + Define::PI / 2 + (Define::PI / 2 * i), power, _bulletType02, _bulletColor02);
			}
		}
	}

	if (_bulletSwitch) {
		if (_counter % 5 == 0 && _counter > _moveTime) {
			for (int i = 0; i < 2; i++) {
				int k = isBulletAvailable();
				shot[k].setFlag(1);
				shot[k].setBullet(x, y, _speed03, GetRand(6) + 0.1 * GetRand(9), power, _bulletType03, _bulletColor03);
			}
		}

		if (_counter % 70 == 0 && _counter > _moveTime) {
			for (int i = 0; i < 24; i++) {
				int k = isBulletAvailable();
				shot[k].setFlag(1);
				shot[k].setBullet(x, y, _speed04, angle + (Define::PI / 12 * i), power, _bulletType04, _bulletColor04);
			}
		}
	}

	// switch bullet type every 150 frames
	if (_counter % 600 == 0 && !_bulletSwitch) {
		_bulletSwitch = true;
	}
	else if (_counter % 600 == 0 && _bulletSwitch) {
		_bulletSwitch = false;
		_angle = 0.0;
	}
}