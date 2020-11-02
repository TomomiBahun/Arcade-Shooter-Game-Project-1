#include "GreenFire02.h"
#include <DxLib.h>
#include "Image.h"
#include "Define.h"

const float ENLARGE = 1.2; // when the enemy image shows up on the gameboard, it is enlarged 1.2 times.

GreenFire02::GreenFire02(float x, float y) : AbstractEnemy(x, y)
{
	_speed = 2.5f;
	_angle = Define::PI / 2;
	_range = 13.0 * ENLARGE;
	_health = 3;
}

bool GreenFire02::update()
{
	if (_counter < 100) {
		_angle = Define::PI / 2;
		_x += cos(_angle) * _speed;
		_y += sin(_angle) * _speed;
	}
	else if (105 <= _counter) {
		_angle = Define::PI / 4;
		_x += cos(_angle) * _speed;
		_y += sin(_angle) * _speed;
	}


	_counter++;
	return isInside();
}

void GreenFire02::draw() const
{
	const static int imgID[4] = { 0, 2, 3, 2 };
	const int handle = Image::getIns()->getGreenFire()[imgID[(_counter / 5) % 4]];
	DrawRotaGraphF(_x, _y, 1.2f, 0.0, handle, TRUE);
}

void GreenFire02::setSize()
{
	int handle = Image::getIns()->getGreenFire()[0];
	GetGraphSize(handle, &_width, &_height);
}