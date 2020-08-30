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

/* After a bullet hits enemy, the bullet should be removed from the game board
   @index this vector holds the index of bullets hit enemy */
void PlayerShot::initBulletsAfterHittingEnemy(std::vector<int>& index)
{
	/*for (int i = 0; i < MAX_BULLETS; i++) {
		for (int j = 0; j < index.size(); i++) {
			if (i == j) {
				shot[i].initBullet(); // if the bullet is in the list, all attributes will be initialized including flag
			}
		}
	}*/
	for (int i = 0; i < index.size(); i++) {
		// index vector is holding index of bullets which hit the enemy
		shot[index[i]].initBullet();
	}
}

/* I want to clone a content of the pointer, but not working now*/
std::shared_ptr<AbstractShot> PlayerShot::clone(/*std::shared_ptr<AbstractShot> base*/)
{
	std::shared_ptr<AbstractShot> clone(/*base*/ this);

	return clone;
}