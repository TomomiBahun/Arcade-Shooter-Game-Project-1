#include "Shot01.h"

Shot01::Shot01() : _speed(6.0), _bulletType(1), _bulletColor(5)
{
}

/* this sets new bullets */
void Shot01::setBullets(float x, float y, float angle, int power)
{
	/* find an available bullet */
	if (_counter % 30 == 0 && _counter != 0) {
		int k = isBulletAvailable();
		shot[k].setFlag(1);
		shot[k].setBullet(x, y, _speed, angle, power, _bulletType, _bulletColor);
		PlaySoundMem(Sound::getIns()->getEnemyShotSound(), DX_PLAYTYPE_BACK);
	}
}