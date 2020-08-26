#include "AbstractEnemy.h"
#include <DxLib.h>
#include "Image.h"
#include "Define.h"
#include "Player.h"

/*float AbstractEnemy::angleEnemyAndPlayer() const
{
	return atan2(_playerY - _y, _playerX - _x);
}*/

AbstractEnemy::AbstractEnemy(float x, float y) :
	_x(x),
	_y(y),
	_speed(0),
	_angle(0),
	_range(0),
	_counter(0),
	_width(0),
	_height(0),
	_health(0)//,
	//_playerX(0),
	//_playerY(0)
{
}

void AbstractEnemy::initialize()
{
	setSize();
}

bool AbstractEnemy::update()
{
	_counter++;
	_x += cos(_angle) * _speed;
	_y += sin(_angle) * _speed;
	return isInside();
}

bool AbstractEnemy::isInside() const
{
	if (_counter < 60) {
		return true;
	}
	if (_x < -_width / 2 || Define::OUTER_W + _width / 2 < _x || _y < -_height / 2 || Define::OUTER_H + _height / 2 < _y) {
		return false;
	}
	return true;
}

void AbstractEnemy::updateHealth(int playerPower)
{
	_health -= playerPower;
}