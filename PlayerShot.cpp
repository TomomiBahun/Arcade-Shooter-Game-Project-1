#include "PlayerShot.h"

/*PlayerShot::PlayerShot() : _counter(0)
{
	// instantiate Bullet objects with (0, 0) coordinates, 0 speed, 0 angle and 0 flag. Properties will be updated.
	for (int i = 0; i < MAX_PLAYERSHOT; i++) {
		shot[i] = Bullet(0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0);
	}
}*/

/*PlayerShot::~PlayerShot()
{
}*/

PlayerShot::PlayerShot() : AbstractShot()
{
}

void PlayerShot::setBullets(float x, float y, float angle, int power)
{
	if (_counter % 5 == 0) {
		int k = isBulletAvailable();
		shot[k].setFlag(1);
		shot[k].setBullet(x, y, _speed, angle, power, _bulletType, _bulletColor);
	}
}