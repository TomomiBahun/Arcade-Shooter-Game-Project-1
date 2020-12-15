#include "YakumoRan.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"
#include "RanShot01.h"
#include "RanShot02.h"
#include "RanShot03.h"
#include "RanShot04.h"
#include "Ranshot05.h"
#include "RanShot06.h"
#include "HitCheck.h"

const static float SHRINK = 0.25;

YakumoRan::YakumoRan() : isReadyForEffect(false), shouldRanHide(false)
{
	/* properties of Ran */
	_speed = 3.0f;
	_angle = 0;
	_range = 180.0 * SHRINK; //Ran icon's radius is 180 pixels
	_healthMax = 1000.0;
	_health = _healthMax;
	_shotIndex = 0;
	_upDownCount = 100;

	_healthRange.push_back({ 1000, 0 });
	//_healthRange.push_back({ 835, 671 });
	//_healthRange.push_back({ 670, 506 });
	//_healthRange.push_back({ 505, 341 });
	//_healthRange.push_back({ 340, 176 });
	//_healthRange.push_back({ 175, 0 });

	/* Ran's shots*/
	shots.push_back(std::make_shared<RanShot06>()); // 0: normal
	//shots.push_back(std::make_shared<RanShot02>()); // 1: spell card
	//shots.push_back(std::make_shared<RanShot03>()); // 2: normal
	//shots.push_back(std::make_shared<RanShot04>()); // 3: spell card
	//shots.push_back(std::make_shared<RanShot05>()); // 4: normal
	//shots.push_back(std::make_shared<RanShot06>()); // 5: spell card

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

	// controls boss's move for RanShot06
	if (_shotIndex == 5) {
		shouldRanHide = shots[_shotIndex]->getShouldRanHide();
	}
	else {
		shouldRanHide = false;
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

	// When boss's health reaches 0
	if (_health < 1) {
		// immediately after player beats the boss, give the boss's location to the defeatEffect class
		if (_canBossStartBullets) {
			bossDefeatEffect.setBossX(_x);
			bossDefeatEffect.setBossY(_y);
		}

		// when player beats the boss, stop adding new bullets and play an effect
		_canBossStartBullets = false; // stop Boss bullets and hide circle image
		shouldRanHide = true; // hide Ran's image from the screen
		_moving = false; // stop moving Ran's image
		bossDefeatEffect.update();

		// after playing an effect, end the stage
		if (bossDefeatEffect.getFlashCount() > 40 && bossDefeatEffect.getFlashFlag() == false) {
			_isStageOver = true; // ends the stage
		}
	}

	/* when _moving, still in process to move to the destination */
	if (_moving) {
		moveBoss();
	}
	_counter++;
	updateCircle(); // update the circle (decoration around the boss image)
	return true;
}

void YakumoRan::draw() const
{
	if (!shouldRanHide) {
		const int handle = Image::getIns()->getYakumoRan();
		DrawRotaGraphF(_x, _y, SHRINK, 0.0, handle, TRUE);
	}

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

	if (bossDefeatEffect.getFlashFlag()) {
		bossDefeatEffect.draw();
	}
}

/* controls boss bullets */
bool YakumoRan::updateShot()
{
	if (_canBossStartBullets) { // when shot is going on
		if (!shouldRanHide) {
			didBulletHitMe();
		}
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

		// move to player's coordinate
		if (shots[_shotIndex]->getMovePattern() == 5) {
			_moving = false; // cancel the previoud pattern
			if (shouldRanHide == true) {
				_x = _playerX;
				_y = _playerY;
			}
		}
	}

	return true;
}