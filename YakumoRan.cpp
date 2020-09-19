#include "YakumoRan.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"
#include "RanShot01.h"
#include "RanShot02.h"
#include "HitCheck.h"

const static float SHRINK = 0.25;

YakumoRan::YakumoRan() : preShot(false), isShot01Ready(false), isShot02Ready(false), isReadyForEffect(false)
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
	shots.push_back(std::make_shared<RanShot02>());
}

bool YakumoRan::update()
{
	/* clear playerShotHitIndex from the last frame */
	HitCheck::getIns()->clearPlayerShotHitIndex();

	/* controls boss's move during conversation*/
	if (_counter == 0) {
		inputDestinationAndTime(70, Define::BOSSBASE_X, Define::BOSSBASE_Y);
		preShot = true;
	}
	if (_counter > 80 && _moving == false && preShot == true && isShot01Ready == false &&) {
		moveUpDown();
	}

	if (isShot01Ready == false && _canBossStartBullets == true) {
		updateShot(0, 0, 0);
	}

	if (isShot01Ready == false && isShot02Ready == false && _health < 970) {
		isShot01Ready = true;
		_canBossStartBullets = false;
		isReadyForEffect = true;
	}

	/* controls effects between normal bullets and spell cards*/
	

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

/* controls boss bullets */
bool YakumoRan::updateShot(int movePattern, float x, float y)
{
	if (_canBossStartBullets) { // when shot is going on
		didBulletHitMe();
		/* keep setting up bullets during boss's shots*/
		shots[_shotIndex]->update();
		shots[_shotIndex]->setBullets(_x, _y, angleBossAndPlayer(), 10);

		// stay at the base position ... movePattern0
		inputDestinationAndTime(70, Define::BOSSBASE_X, Define::BOSSBASE_Y);

		// move up&down ... movePattern1
		if (movePattern == 1) {
			if (_moving == false) {
				moveUpDown();
			}
		}

		// move to the specified location ... movePattern2
	}

	return true;
}