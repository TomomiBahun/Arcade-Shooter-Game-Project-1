#include <DxLib.h>
#include "AbstractBoss.h"
#include "Define.h"
#include "Image.h"
#include "HitCheck.h"

AbstractBoss::AbstractBoss() :
	_counter(0),
	_x(0), _y(0),
	_range(0),
	_speed(0),
	_angle(0),
	_health(0), _healthMax(0),
	_direction(0),
	_moveCounter(0), _moveTime(0),
	_moving(false),
	_v0x(0), _v0y(0),
	_ax(0), _ay(0),
	_preX(0), _preY(0),
	_bottom(false),
	_canBossStartBullets(false),
	_shotIndex(0)
{
}

bool AbstractBoss::update()
{
	_counter++;
	_x += cos(_angle) * _speed;
	_y += sin(_angle) * _speed;
	return true;
}


float AbstractBoss::angleBossAndPlayer()
{
	return atan2(_playerY - _y, _playerX - _x);
}

std::vector<Bullet>& AbstractBoss::getActiveBossBullet(int shotIndex)
{
	_activeBossBullets.clear(); // before updating the vector, delete the elements from the previous frame
	for (int i = 0; i < AbstractBossShot::MAX_BULLETS; i++) {
		if (shots[shotIndex]->shot[i].getFlag() > 0) {
			_activeBossBullets.push_back(shots[shotIndex]->shot[i]);
		}
	}

	return _activeBossBullets;
}

float AbstractBoss::angleBossAndDestination()
{
	//return atan2(_yTo - _y, _xTo - _x);
	return 0.0;
}

/* get player's shot from GameScene class to check if bullets hit the enemy*/
void AbstractBoss::setPlayerShot(AbstractShot& shot)
{
	playerShot = &shot;
}

bool AbstractBoss::didBulletHitMe()
{
	for (int i = 0; i < playerShot->MAX_BULLETS; i++) {
		if (playerShot->shot[i].getFlag() > 0) {
			if (HitCheck::getIns()->didBulletHitEnemy(playerShot->shot, i, _x, _y, _range)) {
				_health -= _playerPower;
				if (_health <= 0) {
					return false; // enemy is dead!
				}
			}
		}
	}
	return true;
}