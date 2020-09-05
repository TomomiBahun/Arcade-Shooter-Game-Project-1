#include <DxLib.h>
#include "AbstractBoss.h"
#include "Define.h"
#include "Image.h"

AbstractBoss::AbstractBoss() :
	_counter(0),
	_x(0), _y(0),
	_speed(0),
	_angle(0),
	_health(0),
	_direction(0),
	_moveCounter(0), _moveTime(0),
	_moving(false),
	_v0x(0), _v0y(0),
	_ax(0), _ay(0),
	_preX(0), _preY(0),
	_bottom(false),
	_canBossStartBullets(false)
{
}

bool AbstractBoss::update()
{
	_counter++;
	_x += cos(_angle) * _speed;
	_y += sin(_angle) * _speed;
	return true;
}