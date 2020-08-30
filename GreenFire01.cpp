#include "GreenFire01.h"
#include <DxLib.h>
#include "Image.h"
#include "Define.h"

const float ENLARGE = 1.2; // when the enemy image shows up on the gameboard, it is enlarged 1.2 times.

GreenFire01::GreenFire01(float x, float y) : AbstractEnemy(x, y)
{
	_speed = 2.0f;
	_angle = Define::PI / 2;
	_range = 13.0 * ENLARGE;
	_health = 3;
}

bool GreenFire01::update()
{
	if (_angle < Define::PI && _counter % 50 == 0) {
		_angle += Define::PI / 10;
	}
	_counter++;
	_x += cos(_angle) * _speed;
	_y += sin(_angle) * _speed;
	return isInside();
}

void GreenFire01::draw() const
{
	const static int imgID[4] = { 0, 2, 3, 2 };
	const int handle = Image::getIns()->getGreenFire()[imgID[(_counter / 5) % 4]];
	DrawRotaGraphF(_x, _y, 1.2f, 0.0, handle, TRUE);
}

void GreenFire01::setSize()
{
	int handle = Image::getIns()->getGreenFire()[0];
	GetGraphSize(handle, &_width, &_height);
}