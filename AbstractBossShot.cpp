#include "AbstractBossShot.h"

AbstractBossShot::AbstractBossShot() : _counter(0), _hideRan(false)
{
	// instantiate Bullet objects with (0, 0) coordinates, 0 speed, 0 angle and 0 flag. Properties will be updated.
	for (int i = 0; i < MAX_BULLETS; i++) {
		shot[i] = Bullet(0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0);
	}
}
/*AbstractShot::~AbstractShot()
{
}*/

bool AbstractBossShot::update()
{
	// to make shapes and move.... update the angle, speed etc. here

	_counter++;
	// update the bullet properties if the bullet's flag is on (if the bullet is on the board)
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (shot[i].getFlag() > 0) {
			shot[i].update();
		}
		else {
			shot[i].initBullet();
		}
	}
	return true;
}

void AbstractBossShot::draw() const
{
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (shot[i].getFlag() > 0) {
			shot[i].draw();
		}
	}
}

int AbstractBossShot::isBulletAvailable() const
{
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (shot[i].getFlag() < 1) {
			return i;
		}
	}

	return -1; // if none is available
}