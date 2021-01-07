#include "Player.h"
#include "keyboard.h"
#include <DxLib.h>
#include "Image.h"
#include "Define.h"
#include "ImageBullet.h"
#include "Sound.h"

using namespace std;

Player::Player() :
	_counter(0),
	_slow(false),
	_boxAngle(0.0),
	_x(Define::CENTER_X),
	_y(Define::CENTER_Y + 500),
	_range(0.0), // Reimu->10.5, Marisa->??
	direction(0), directionCount(0),
	_power(0), // Reimu->1, Marisa->2
	_health(50),
	_speed(0), // Reimu->6, Marisa->8
	_noHitTimer(0)
{
}

bool Player::update()
{
	/* check if any of enemy bullet hits the player
	   if player gets hit, decrease the player health and set the noHitTimer*/
	if (_noHitTimer == 0) {
		if (didBulletHitMe()) {
			_noHitTimer = 12;
		}
	}
	else {
		if (_counter % 7 == 0)
			_noHitTimer--;
	}

	/* after checking all of the bullets in this frame, init the vector */
	_activeEnemyBullets.clear();
	_activeBossBullets.clear();

	/* continue rotating hitBox image*/
	if (_boxAngle <= 2*Define::PI) {
		_boxAngle += Define::PI / 180;
	}
	else {
		_boxAngle = 0.0;
	}

	_counter++;
	move();
	shotBullets();
	_playerShot.initBulletsAfterHittingEnemy(HitCheck::getIns()->getPlayerShotHitIndex());
	_playerShot.update();
	return true;
}

/* get all of the active bullets */
std::vector<Bullet>& Player::getActivePlayerBullet()
{
	_activePlayerBullets.clear(); // before updating the vector, delete the elements from the previous frame
	for (int i = 0; i < AbstractShot::MAX_BULLETS; i++) {
		if (_playerShot.shot[i].getFlag() > 0) {
			_activePlayerBullets.push_back(_playerShot.shot[i]);
		}
	}
	return _activePlayerBullets;
}

/* get enemy's bullet information at Player class*/
void Player::setActiveEnemyBullets(std::vector<Bullet>& enemyBullets)
{
	_activeEnemyBullets.clear(); // delete all elements in vector before updating it
	for (int i = 0; i < enemyBullets.size(); i++) {
		_activeEnemyBullets.push_back(enemyBullets[i]);
	}
}

/* get boss's bullet information at Player class*/
void Player::setActiveBossBullets(std::vector<Bullet>& bossBullets)
{
	_activeEnemyBullets.clear(); // delete all elements in vector before updating it
	for (int i = 0; i < bossBullets.size(); i++) {
		_activeBossBullets.push_back(bossBullets[i]);
	}
}


/* Player's shot properties */
void Player::shotBullets()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) > 0) {
		/* when Slow-move mode, bullets are closer to center. */
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LSHIFT) > 0) {
			_playerShot.setBullets(_x + 15, _y - 8, Define::PI / 2 * 3, _power);
			_playerShot.setBullets(_x - 15, _y - 8, Define::PI / 2 * 3, _power);
		}
		else {
			_playerShot.setBullets(_x + 25, _y - 8, Define::PI / 2 * 3, _power);
			_playerShot.setBullets(_x - 25, _y - 8, Define::PI / 2 * 3, _power);
		}
	}
}

/* Check if enemy's bullet hits the player.
   This function can become very expensive easily, because there can be so many bullets on the screen.
   Check only the area around the player...
   _x-100 < check area < _x+100, _y-100 < check area < _y+100 */
bool Player::didBulletHitMe()
{
	for (int i = 0; i < _activeEnemyBullets.size(); i++) {
		if (_y - 100 < _activeEnemyBullets[i].getY() && _activeEnemyBullets[i].getY() < _y + 100) {
			if (_x < _activeEnemyBullets[i].getX() && _activeEnemyBullets[i].getX() < _x + 100) {
				if (HitCheck::getIns()->didBulletHitPlayer(_activeEnemyBullets, i, _x, _y, _range)) {
					_health -= 10; // all enemy bullets power are 10
					PlaySoundMem(Sound::getIns()->getGetHitSound(), DX_PLAYTYPE_BACK); // play hit sound
					return true;
				}
			}
		}
	}

	for (int i = 0; i < _activeBossBullets.size(); i++) {
		if (_y - 100 < _activeBossBullets[i].getY() && _activeBossBullets[i].getY() < _y + 100) {
			if (_x < _activeBossBullets[i].getX() && _activeBossBullets[i].getX() < _x + 100) {
				if (HitCheck::getIns()->didBulletHitPlayer(_activeBossBullets, i, _x, _y, _range)) {
					_health -= 10; // all enemy bullets power are 10
					PlaySoundMem(Sound::getIns()->getGetHitSound(), DX_PLAYTYPE_BACK); // play hit sound
					return true;
				}
			}
		}
	}
	return false;
}