#include "YakumoRan.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"
#include "RanShot01.h"
#include "HitCheck.h"

const static float SHRINK = 0.25;

YakumoRan::YakumoRan()
{
	/* properties of Ran */
	_speed = 3.0f;
	_angle = 0;
	_range = 180.0 * SHRINK; //Ran icon's radius is 180 pixels
	_healthMax = 1000.0;
	_health = _healthMax;
	_shotIndex = 0;

	/* Ran's shots*/
	shots.push_back(std::make_shared<RanShot01>());
}

bool YakumoRan::update()
{
	/* clear playerShotHitIndex from the last frame */
	HitCheck::getIns()->clearPlayerShotHitIndex();

	/* controls boss's move during conversation*/
	if (_counter == 0) {
		inputDestinationAndTime(70, Define::BOSSBASE_X, Define::BOSSBASE_Y);
	}
	if(_counter > 80 && _moving == false && _canBossStartBullets == false) {
		moveUpDown();
	}

	if (_canBossStartBullets) { // when shot is going on
		didBulletHitMe();
		/* keep setting up bullets during boss's shots*/
		shots[_shotIndex]->update();
		shots[_shotIndex]->setBullets(_x, _y, angleBossAndPlayer(), 10);
		if (_moving == false) {
			moveUpDown();
		}
	}

	/* when _moving, still in process to move to the destination */
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

	if (_canBossStartBullets) {
		drawHealth();
		shots[_shotIndex]->draw();
	}
}

/* Input the destination and calculate velocity & acceleration for smooth move
*  _moving should be false when using this function
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

/* Move boss icon based on calculation done by inputDestinationAndTime()
   Always call inputDestinationAndTime() first */
void YakumoRan::moveBoss()
{
	_x = _preX - ((_v0x * _moveCounter) - 0.5 * _ax * _moveCounter * _moveCounter); // current x
	_y = _preY - ((_v0y * _moveCounter) - 0.5 * _ay * _moveCounter * _moveCounter); // current y
	_moveCounter++;
	if (_moveCounter >= _moveTime) { // if spent specified time, stop moving
		_moving = false;
	}
}

/* Move boss icon around the base position. Make it look like floating in the air... 
   _moving should be false when using this function */
void YakumoRan::moveUpDown()
{
	if (_bottom) {
		inputDestinationAndTime(95, Define::BOSSBASE_X, Define::BOSSBASE_Y);
		_bottom = false;
	}
	else {
		inputDestinationAndTime(95, Define::BOSSBASE_X, Define::BOSSBASE_Y + 50);
		_bottom = true;
	}
}
/* When boss shot is ready, show the health meter. When drawing the health meter for the first time,
   Make it look like that the meter is going up until the max-health */
void YakumoRan::drawHealth() const
{
	int drawIndexMax = Define::INNER_W * 0.90 * _health / _healthMax;
	int drawIndex = _counter * 5;
	if (_counter*5 > drawIndexMax) {
		drawIndex = drawIndexMax;
	}
	else {
		drawIndex = _counter*5;
	}
	if (_healthMax == 0) { printfDx("enemy health error");return; }
	for (int i = 0; i < drawIndex; i++) {
		DrawGraph(10 + Define::IN_X + i, 2 + Define::IN_Y, Image::getIns()->getBossHealth(), FALSE);
	}
}