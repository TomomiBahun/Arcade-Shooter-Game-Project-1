#include "YakumoRan.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"
#include "RanShot01.h"
#include "RanShot02.h"
#include "RanShot03.h"
#include "RanShot04.h"
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

	_healthRange.push_back({ 1000, 851 });
	_healthRange.push_back({ 850, 701 });
	_healthRange.push_back({ 700, 551 });
	_healthRange.push_back({ 550, 401 });

	/* Ran's shots*/
	shots.push_back(std::make_shared<RanShot04>()); // 0: normal
	shots.push_back(std::make_shared<RanShot02>()); // 1: spell card
	shots.push_back(std::make_shared<RanShot03>()); // 2: normal
	shots.push_back(std::make_shared<RanShot04>()); // 3: spell card
}

bool YakumoRan::update()
{
	/* clear playerShotHitIndex from the last frame */
	HitCheck::getIns()->clearPlayerShotHitIndex();

	/* controls boss's move during conversation*/
	if (_counter == 0) {
		inputDestinationAndTime(70, Define::BOSSBASE_X, Define::BOSSBASE_Y);
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
		if (_shotIndex % 2 == 0 || _shotIndex == 0) { // Activate effect when normal bullet -> spell card
			effect.update();
			_bossBackOn = true;
			if (!effect.getEffectStatus()) {
				isReadyForEffect = false;
				_canBossStartBullets = true;
				_shotIndex++;
			}
		}
		else { // No effect when spell card -> normal bullet
			nullEffect.update();
			_bossBackOn = false;
			if (!nullEffect.getEffectStatus()) {
				isReadyForEffect = false;
				_canBossStartBullets = true;
				_shotIndex++;
			}
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

		// do nothing at one location
		if (shots[_shotIndex]->getMovePattern() == 3) {
			// do nothing...
		}

		// move to the specified location and move up&down ... _movePattern == 4
		if (shots[_shotIndex]->getMovePattern() == 4) {
			int random = GetRand(4);
			int moveX = 100 + 100 * random;
			int moveY = Define::BOSSBASE_Y;
			if (_moving == false) {
				inputDestinationAndTime(150, moveX, moveY);
			}
		}
	}

	return true;
}