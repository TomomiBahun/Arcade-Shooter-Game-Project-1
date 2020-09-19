#include "RanShot02.h"
#include "Define.h"

RanShot02::RanShot02() : 
	_bulletType01(ImageBullet::sharpBullet), _bulletType02(ImageBullet::bigBall),
	_speed01(7.0), _speed02(2.0),
	_bulletColor01(ImageBullet::eAqua), _bulletColor02(ImageBullet::eBlue)
{
}

/* this sets new bullets */
void RanShot02::setBullets(float x, float y, float angle, int power)
{
	/* find an available bullet */
	if (_counter % 10 == 0 && _counter != 0) {
		for (int i = 0; i < 4; i++) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed01, angle + Define::PI / 2 + (Define::PI / 2 * i), power, _bulletType01, _bulletColor01);
		}
	}

	/*if (_counter % 30 == 0 && _counter != 0) {
		for (int i = 0; i < 24; i++) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed02, angle + (Define::PI / 12 * i), power, _bulletType01, _bulletColor02);
		}
	}*/
}