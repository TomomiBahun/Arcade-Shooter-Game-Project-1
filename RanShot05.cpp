#include "RanShot05.h"
#include "Define.h"
#include <DxLib.h>

RanShot05::RanShot05(): _bulletType(ImageBullet::sharpBullet),
	_speed01(6.0), _speed02(1.5),
	_bulletColor01(ImageBullet::eAqua), _bulletColor02(ImageBullet::eGreen),
	_randomNum(0)
{
	_angle = 0.0;
	_movePattern = 1; // moveUp&Down
}

void RanShot05::setBullets(float x, float y, float angle, int power) {
	/* find an available bullet */
	if (_angle <= 2 * Define::PI) {
		_angle -= Define::PI / 360;
	}
	if (_counter % 10 == 0 && _counter > 50) {
		for (int i = 0; i < 8; i++) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed01, _angle + Define::PI / 2 - (Define::PI / 4 * i), power, _bulletType, _bulletColor01);
		}
	}

	if (_counter % 30 == 0 && _counter > 50) {
		for (int i = 0; i < 28; i++) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed02, angle + (Define::PI / 14 * i), power, _bulletType, _bulletColor02);
		}
		PlaySoundMem(Sound::getIns()->getEnemyShotSound(), DX_PLAYTYPE_BACK);
	}
}