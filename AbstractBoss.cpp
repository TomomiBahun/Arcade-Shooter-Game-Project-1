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
	_moveToLoc(true), _upDownCount(0),
	_moveCounter(0), _moveTime(0),
	_moving(false),
	_v0x(0), _v0y(0),
	_ax(0), _ay(0),
	_preX(0), _preY(0),
	_bottom(false),
	_canBossStartBullets(false), _canBossCome(false),
	_isBossTalking(true), _isStageOver(false),
	_shotIndex(0),
	_circleAngle(0.0), _circleExpand(0.0), _shrinkOrEnlarge(0), _bossBackOn(false)
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

/* Input the destination and calculate velocity & acceleration for smooth move
*  _moving should be false when using this function
   @t time (num of frames) to spend for move
   @xDest destination
   @yDest destination */
void AbstractBoss::inputDestinationAndTime(int t, float xDest, float yDest)
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

/* Move boss icon based on calculation done by inputDestinationAndTime()
   Always call inputDestinationAndTime() first */
void AbstractBoss::moveBoss()
{
	if (_moveCounter <= _moveTime) {
		_x = _preX - ((_v0x * _moveCounter) - 0.5 * _ax * _moveCounter * _moveCounter); // current x
		_y = _preY - ((_v0y * _moveCounter) - 0.5 * _ay * _moveCounter * _moveCounter); // current y
		_moveCounter++;
	}
	if (_moveCounter >= _moveTime) { // if spent specified time, stop moving
		_moving = false;
	}
}

/* Move boss icon around the base position. Make it look like floating in the air...
   _moving should be false when using this function */
void AbstractBoss::moveUpDown()
{

	if (_bottom) {
		inputDestinationAndTime(70, _x, _y - 25);
		_bottom = false;
	}
	else {
		inputDestinationAndTime(70, _x, _y + 25);
		_bottom = true;
	}
	_moving = true;
}

/* When boss shot is ready, show the health meter. When drawing the health meter for the first time,
   make it look like that the meter is going up until the max-health */
void AbstractBoss::drawHealth() const
{
	int drawIndexMax = Define::INNER_W * 0.90 * _health / _healthMax;
	int drawIndex = _counter * 5;
	if (_counter * 5 > drawIndexMax) {
		drawIndex = drawIndexMax;
	}
	else {
		drawIndex = _counter * 5;
	}
	if (_healthMax == 0) { printfDx("enemy health error");return; }
	for (int i = 0; i < drawIndex; i++) {
		DrawGraph(10 + Define::IN_X + i, 2 + Define::IN_Y, Image::getIns()->getBossHealth(), FALSE);
	}
}

bool AbstractBoss::updateCircle()
{
	/* Rotate background circle image*/
	if (_circleAngle <= 2 * Define::PI) {
		_circleAngle += (Define::PI / 180*2);
	}
	else {
		_circleAngle = 0.0;
	}

	if (_canBossStartBullets) {
		if (_shrinkOrEnlarge == 0) { // Enlarge the circle quickly... only when boss start bullets for the first time
			if (_circleExpand < 1.5) {
				_circleExpand += 0.02;
			}
			else {
				_circleExpand = 1.5;
				_shrinkOrEnlarge = 2;
			}
		}
		else if (_shrinkOrEnlarge == 1) { // Enlarge the circle slowly...
			if (_circleExpand < 1.5) {
				_circleExpand += 0.002;
			}
			else {
				_circleExpand = 1.5;
				_shrinkOrEnlarge = 2;
			}
		}else{							// Shrink the circle slowly...
			if (_circleExpand > 1.2) {
				_circleExpand -= 0.002;
			}
			else {
				_circleExpand = 1.2;
				_shrinkOrEnlarge = 1;
			}
		}
	}

	return true;
}

void AbstractBoss::drawCircle() const
{
	DrawRotaGraphF(_x, _y, _circleExpand, _circleAngle, Image::getIns()->getCircle()[1], TRUE);
}