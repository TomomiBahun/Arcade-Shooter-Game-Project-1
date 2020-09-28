#include "YakumoRan.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"
#include "RanShot01.h"
#include "RanShot02.h"
#include "HitCheck.h"

const static float SHRINK = 0.25;

YakumoRan::YakumoRan() : isShot01Ready(false), isShot02Ready(false), isReadyForEffect(false)
{
	/* properties of Ran */
	_speed = 3.0f;
	_angle = 0;
	_range = 180.0 * SHRINK; //Ran icon's radius is 180 pixels
	_healthMax = 1000.0;
	_health = _healthMax;
	_shotIndex = 0;
	_upDownCount = 100;

	_healthRange.push_back({ 1000, 971 });
	_healthRange.push_back({ 970, 870 });

	/* Ran's shots*/
	shots.push_back(std::make_shared<RanShot01>());
	shots.push_back(std::make_shared<RanShot02>());
}

bool YakumoRan::update()
{
	/* clear playerShotHitIndex from the last frame */
	HitCheck::getIns()->clearPlayerShotHitIndex();

	/* controls boss's move during conversation*/
	if (_counter == 0) {
		inputDestinationAndTime(70, Define::BOSSBASE_X, Define::BOSSBASE_Y);
		//preShot = true;
	}
	if (_counter > 80 && _moving == false && _health == _healthMax) {
		moveUpDown();
	}

	/* Use certain bullets when boss has specific amount of health left*/
	if (_healthRange.at(_shotIndex)[1] < _health <= _healthRange.at(_shotIndex)[0] && _canBossStartBullets == true) {
		updateShot();
		if (_health < _healthRange.at(_shotIndex)[1]) {
			_canBossStartBullets = false;
			isReadyForEffect = true;
		}
	}

	/* controls effects between normal bullets and spell cards*/
	if (isReadyForEffect) {
		effect.update();
		if (!effect.getEffectStatus()) {
			isReadyForEffect = false;
			_canBossStartBullets = true;
			_shotIndex++;
		}
	}

	/* when _moving, still in process to move to the destination */
	if (_moving) {
		moveBoss();
	}
	_counter++;
	updateCircle();
	return true;
}

void YakumoRan::draw() const
{
	const int handle = Image::getIns()->getYakumoRan();
	DrawRotaGraphF(_x, _y, SHRINK, 0.0, handle, TRUE);

	// when conversation is done, start drawing health and keep it there
	if (_isBossTalking == false) {
		drawHealth();
	}

	if (_canBossStartBullets) {
		shots[_shotIndex]->draw();
		drawCircle();
	}

	if (isReadyForEffect) {
		effect.draw();
	}
}

/* controls boss bullets */
bool YakumoRan::updateShot()
{
	if (_canBossStartBullets) { // when shot is going on
		didBulletHitMe();
		/* keep setting up bullets during boss's shots*/
		shots[_shotIndex]->update();
		shots[_shotIndex]->setBullets(_x, _y, angleBossAndPlayer(), 10);

		// stay at the base position ... _movePattern == 0
		if (shots[_shotIndex]->getMovePattern() == 0) {
			inputDestinationAndTime(70, Define::BOSSBASE_X, Define::BOSSBASE_Y);
		}

		// move up&down ... _movePattern == 1
		if (shots[_shotIndex]->getMovePattern() == 1) {
			if (_moving == false) {
				moveUpDown();
			}
		}

		// move to the specified location ... _movePattern == 2
		if (shots[_shotIndex]->getMovePattern() == 2) {
			if (_moving == false) {
				inputDestinationAndTime(shots[_shotIndex]->getMoveTime(), shots[_shotIndex]->getMoveX(), shots[_shotIndex]->getMoveY());
			}
		}

		// move to the specified location and move up&down ... _movePattern == 3
		/*if (shots[_shotIndex]->getMovePattern() == 3) {
			if (_moving == false && _moveToLoc == true) {
				inputDestinationAndTime(shots[_shotIndex]->getMoveTime(), shots[_shotIndex]->getMoveX(), shots[_shotIndex]->getMoveY());
				_upDownCount = _moveTime;
			}
			if (_moving == false && _moveToLoc == false && _upDownCount != 0) {
				moveUpDown();
			}
			if (_upDownCount == 0) {
				_moveToLoc = true;
			}
			else {
				_upDownCount--;
			}
		}*/
	}

	return true;
}