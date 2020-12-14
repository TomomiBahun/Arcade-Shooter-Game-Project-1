#include "RanShot06.h"
#include "Define.h"
#include <DxLib.h>

RanShot06::RanShot06() :_bulletType1(ImageBullet::bigBall), _bulletType2(ImageBullet::smallBall),
	_speed01(6.0), _speed02(5.0),
	_bulletColor01(ImageBullet::eAqua), _bulletColor02(ImageBullet::eBlue),
	_baseCounter(0), _baseCounter2(0), _hideCounter(0), _appearCounter(0), _soundCounter(0),
	_bulletX(0.0), _bulletY(0.0)
{
	_angle = 0.0;
	_movePattern = 5;
}

void RanShot06::setBullets(float x, float y, float angle, int power) {
	if (_counter % 150 == 0 && _counter > 50) {
		setCircleBullets(x, y, power, 0);
		// bullets coming towards the player
		if (_counter > 150) {
			int k = isBulletAvailable();
			shot[k].setFlag(1);
			shot[k].setBullet(x, y, _speed01, angle, power, _bulletType1, _bulletColor02);
			int h = isBulletAvailable();
			shot[h].setFlag(1);
			shot[h].setBullet(x, y, _speed01, angle + (Define::PI/50), power, _bulletType2, _bulletColor02);
			int v = isBulletAvailable();
			shot[v].setFlag(1);
			shot[v].setBullet(x, y, _speed01, angle - (Define::PI/50), power, _bulletType2, _bulletColor02);
			int g = isBulletAvailable();
			shot[g].setFlag(1);
			shot[g].setBullet(x, y, _speed02, angle + (Define::PI/60), power, _bulletType2, _bulletColor02);
			int f = isBulletAvailable();
			shot[f].setFlag(1);
			shot[f].setBullet(x, y, _speed02, angle - (Define::PI/60), power, _bulletType2, _bulletColor02);
		}
		PlaySoundMem(Sound::getIns()->getEnemyShotSound(), DX_PLAYTYPE_BACK);
		_baseCounter = _counter + 10;
		_baseCounter2 = _counter + 20;
		_hideCounter = _counter + 10;
		_appearCounter = _counter + 40;
		_soundCounter = _counter + 80;
		_bulletX = x;
		_bulletY = y;
	}

	if (_counter == _baseCounter && _counter > 50) {
		setCircleBullets(_bulletX, _bulletY, power, 0.1);
		PlaySoundMem(Sound::getIns()->getEnemyShotSound(), DX_PLAYTYPE_BACK);
	}

	if (_counter == _baseCounter2 && _counter > 50) {
		setCircleBullets(_bulletX, _bulletY, power, 0.2);
		PlaySoundMem(Sound::getIns()->getEnemyShotSound(), DX_PLAYTYPE_BACK);
	}

	if (_hideCounter != 0 && _appearCounter != 0) {
		if (_counter == _hideCounter && _counter > 50) {
			_hideRan = true;
		}

		if (_counter == _appearCounter && _counter > 50) {
			_hideRan = false;
		}
	}

	if (_counter == _soundCounter && _counter > 50) {
		PlaySoundMem(Sound::getIns()->getBulletEffectSound(), DX_PLAYTYPE_BACK);
	}
}

void RanShot06::setCircleBullets(float x, float y, int power, double decreaseSpeedRate) {
	for (int i = 0; i < 20; i++) {
		int k = isBulletAvailable();
		shot[k].setFlag(1);
		shot[k].setBullet(x, y, _speed01 - decreaseSpeedRate, _angle + Define::PI / 2 - (Define::PI / 10 * i), power, _bulletType1, _bulletColor01);
	}
}
