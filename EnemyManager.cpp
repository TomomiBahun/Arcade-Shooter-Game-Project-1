#include "EnemyManager.h"
#include "Define.h"
#include "BlueFire.h"
#include "GreenFire.h"
#include "Shot01.h"
#include "Shot02.h"
#include "HitCheck.h"
#include <DxLib.h>

using namespace std;

/* This class holds each enemy object in the list */
EnemyManager::EnemyManager()
{
	// One shot type per regular enemy. Total num of _list = Total num of _shotList
	_list.emplace_back(make_shared<BlueFire>(Define::CENTER_X, 100));
	_shotList.emplace_back(make_shared<Shot01>());

	//_list.emplace_back(make_shared<GreenFire>(Define::CENTER_X + 200, 100));
	//_shotList.emplace_back(make_shared<Shot02>());

	for (auto enemy : _list) {
		enemy->initialize();
	}
}

bool EnemyManager::update()
{
	// trying std::vector instead of std::list
	/*for (auto it = _list.begin(); it != _list.end();) {
		if ((*it)->update() == false) {
			it = _list.erase(it);
		}
		else {
			it++;
			// shot01.setShot(); // if the enemy is still on the board
		}
	}*/

	/* keep updating the enemies in _list.
	   If enemy gets out of the game board OR enemy health is 0, erase the enemy object from the _list.
	   Also enemy will keep shooting bullets while they are inside the game board*/
	for (int i = 0; i < _list.size(); i++) {
		if (_list[i]->update() == false || didBulletHitMe(_list[i]) == false) {
			_list.erase(_list.begin()+ i);
		}
		else {
			//if(i <= _shotList.size() - 1) // I feel like I can organize this part more
			float currentAngle = angleEnemyAndPlayer(_list[i]->getX(), _list[i]->getY());
			_shotList[i]->setBullets(_list[i]->getX(), _list[i]->getY(), currentAngle, ENEMY_SHOT_POWER);
			// depending on the shot type, i might want to set just coordinates.
		}

	}
	/* keep updating the bullets inside the game board*/
	for (int i = 0; i < _shotList.size(); i++) {
		_shotList[i]->update();
	}
	return true;
}

void EnemyManager::draw() const
{
	DrawFormatString(0, 20, GetColor(255, 255, 255), "The num of enemy = %d", _list.size());
	for (const auto enemy : _list) {
		enemy->draw();
	}
	for (const auto shot : _shotList) {
		shot->draw();
	}
}

/* get all of the active bullets */
std::vector<Bullet>& EnemyManager::getActiveEnemyBullet()
{
	_activeEnemyBullets.clear(); // before updating the vector, delete the elements from the previous frame
	for (int i = 0; i < _shotList.size(); i++) {
		for (int j = 0; j < AbstractShot::MAX_BULLETS; j++) {
			if (_shotList[i]->shot[j].getFlag() > 0) {
				_activeEnemyBullets.push_back(_shotList[i]->shot[j]);
			}
		}
	}
	return _activeEnemyBullets;
}

void EnemyManager::setActivePlayerBullets(std::vector<Bullet>& playerBullets)
{
	_activePlayerBullets.clear(); // delete all elements in vector before updating it
	for (int i = 0; i < playerBullets.size(); i++) {
		_activePlayerBullets.push_back(playerBullets[i]);
	}
}

float EnemyManager::angleEnemyAndPlayer(float enemyX, float enemyY) const
{
	return atan2(_playerY - enemyY, _playerX - enemyX);
}

/* return false if enemy is dead after this frame. return true if enemy is still alive.*/
bool EnemyManager::didBulletHitMe(std::shared_ptr<AbstractEnemy> enemy)
{
	/*for (int i = 0; i < _activePlayerBullets.size(); i++) {
		if (HitCheck::getIns()->didBulletHitMe(_activePlayerBullets, i, enemy->getX(), enemy->getY(), enemy->getRange())) {
			enemy->updateHealth(_playerPower); // decrease enemy health
			if (enemy->getHealth() <= 0) {
				return false; // enemy is dead!
			}
		}
	}
	return true; // enemy is still alive*/

	for (int i = 0; i < playerShot->MAX_BULLETS; i++) {
		if (playerShot->shot[i].getFlag() > 0) {
			if (HitCheck::getIns()->didBulletHitMe(playerShot->shot, i, enemy->getX(), enemy->getY(), enemy->getRange(), 1)) {
				enemy->updateHealth(_playerPower); // decrease enemy health
				playerShotIndex.push_back(i);
				if (enemy->getHealth() <= 0) {
					return false; // enemy is dead!
				}
			}
		}
	}
}

void EnemyManager::setPlayerShot(AbstractShot& shot)
{
	playerShot = &shot;
}