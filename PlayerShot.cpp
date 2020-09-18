#include "PlayerShot.h"

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
	for (int i = 0; i < index.size(); i++) {
		// index vector is holding index of bullets which hit the enemy
		shot[index[i]].initBullet();
	}
}