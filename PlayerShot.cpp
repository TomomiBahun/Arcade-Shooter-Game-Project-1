#include "PlayerShot.h"
#include "ImageBullet.h"

const static int REIMU_POWER = 1;
const static int MARISA_POWER = 2;

PlayerShot::PlayerShot() : AbstractShot()
{
}

void PlayerShot::setBullets(float x, float y, float angle, int power)
{
	if (power == REIMU_POWER) {
		if (_counter % 7 == 0) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed, angle, power, ImageBullet::eBulletType::reimuBullet, 0);
		}
	}
	else if (power == MARISA_POWER) {
		if (_counter % 11 == 0) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed, angle, power, ImageBullet::eBulletType::marisaBullet, 0);
		}
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