#include "YakumoRan.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"

const static float SHRINK = 0.25;

YakumoRan::YakumoRan()
{
	_speed = 3.0f;
	_angle = 0;
	_range = 13.0 * SHRINK;
	_health = 15;
}

bool YakumoRan::update()
{
	if (_counter == 0) {
		inputDestinationAndTime(70, Define::CENTER_X, Define::CENTER_Y - 150);
	}
	if(_counter > 80 && _moving == false && _canBossStartBullets == false) {
		moveUpDown();
	}

	/* controls boss's move */
	if (_moving) {
		moveBoss();
	}
	_counter++;
	return true;
}

void YakumoRan::draw() const
{
	const int handle = Image::getIns()->getYakumoRan();
	DrawRotaGraphF(_x, _y, SHRINK, 0.0, handle, TRUE);
}


float YakumoRan::angleBossAndPlayer()
{
	//return atan2(_playerY - _y, _playerX - _x);
	return 0.0;
}

float YakumoRan::angleBossAndDestination()
{
	//return atan2(_yTo - _y, _xTo - _x);
	return 0.0;
}

/* input the destination and calculate velocity & acceleration for smooth move
   @t time (num of frames) to spend for move
   @xDest destination
   @yDest destination */
void YakumoRan::inputDestinationAndTime(int t, float xDest, float yDest)
{
	float maxX, maxY;
	_moveTime = t; // time to spend to get to the destination
	_moveCounter = 0; // init moveCounter: if moveCounter == moveTime then stop moving
	_moving = true;
	maxX = _x - xDest; // distance to move
	_v0x = 2 * maxX / t; // initial velocity x
	_ax = 2 * maxX / (t * t); // acceleration
	_preX = _x; // x coordinate before moving
	maxY = _y - yDest; // distance to move
	_v0y = 2 * maxY / t; // initial velocity y
	_ay = 2 * maxY / (t * t); // acceleration
	_preY = _y; // y coordinate before moving
}

/* move boss icon based on calculation done by inputDestinationAndTime()
   always call inputDestinationAndTime() first*/
void YakumoRan::moveBoss()
{
	_x = _preX - ((_v0x * _moveCounter) - 0.5 * _ax * _moveCounter * _moveCounter); // current x
	_y = _preY - ((_v0y * _moveCounter) - 0.5 * _ay * _moveCounter * _moveCounter); // current y
	_moveCounter++;
	if (_moveCounter >= _moveTime) { // if spent specified time, stop moving
		_moving = false;
	}
}

/* move boss icon around the base position
   make it look like floating in the air... */
void YakumoRan::moveUpDown()
{
	if (_bottom) {
		inputDestinationAndTime(95, Define::CENTER_X, Define::CENTER_Y - 150);
		_bottom = false;
	}
	else {
		inputDestinationAndTime(95, Define::CENTER_X, Define::CENTER_Y - 100);
		_bottom = true;
	}
}