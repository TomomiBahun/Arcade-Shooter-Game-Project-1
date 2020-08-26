#include "Shot02.h"
#include "Define.h"

Shot02::Shot02() : _speed(5.0), _bulletType(1), _bulletColor(2)
{
}

/* this sets new bullets */
void Shot02::setBullets(float x, float y, float angle, int power)
{
	/* find an available bullet */
	if (_counter % 15 == 0 && _counter != 0) {
		int k = isBulletAvailable();
		shot[k].setFlag(1);
		shot[k].setBullet(x, y, _speed, angle - Define::PI/10, power,  _bulletType, _bulletColor);
		int p = isBulletAvailable();
		shot[p].setFlag(1);
		shot[p].setBullet(x, y, _speed, angle + Define::PI/10, power, _bulletType, _bulletColor);
	}
}