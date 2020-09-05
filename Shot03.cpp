#include "Shot03.h"
#include "Define.h"

Shot03::Shot03() : _speed(3.0), _bulletType(1), _bulletColor(4)
{
	_angle = Define::PI / 2;
}

/* this sets new bullets */
void Shot03::setBullets(float x, float y, float angle, int power)
{
	_angle += Define::PI / 50;
	/* find an available bullet */
	if (_counter % 5 == 0 && _counter != 0) {
		int k = isBulletAvailable();
		shot[k].setFlag(1);
		shot[k].setBullet(x, y, _speed, _angle, power, _bulletType, _bulletColor);
	}
}