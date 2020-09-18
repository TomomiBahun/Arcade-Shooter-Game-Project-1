#include "RanShot01.h"
#include "Define.h"

RanShot01::RanShot01() : _bulletType(ImageBullet::sharpBullet),
	_speed01(7.0), _speed02(2.0),
	_bulletColor01(ImageBullet::eAqua), _bulletColor02(ImageBullet::eBlue)
{
}

/* this sets new bullets */
void RanShot01::setBullets(float x, float y, float angle, int power)
{
	/* find an available bullet */
	if (_counter % 14 == 0 && _counter != 0) {
		for (int i = 0; i < 24; i++) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed01, angle + Define::PI/8 + (Define::PI / 12 * i), power, _bulletType, _bulletColor01);
		}
	}

	if (_counter % 30 == 0 && _counter != 0) {
		for (int i = 0; i < 24; i++) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed02, angle + (Define::PI / 12 * i), power, _bulletType, _bulletColor02);
		}
	}
}