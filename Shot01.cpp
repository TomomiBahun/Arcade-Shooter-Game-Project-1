#include "Shot01.h"

Shot01::Shot01() : _speed(3.0), _bulletType(1), _bulletColor(5)
{
}

/* this sets new bullets */
void Shot01::setBullets(float x, float y, float angle, int power)
{
	/* find an available bullet */
	if (_counter % 50 == 0 && _counter != 0) {
		int k = isBulletAvailable();
		shot[k].setFlag(1);
		shot[k].setBullet(x, y, _speed, angle, power, _bulletType, _bulletColor);
	}
}

/* clone a content of the pointer (in progress)*/
std::shared_ptr<AbstractShot> Shot01::clone(/*std::shared_ptr<AbstractShot> base*/)
{
	std::shared_ptr<AbstractShot> clone(/*base*/ this);

	return clone;
}