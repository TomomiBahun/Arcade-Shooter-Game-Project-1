#include "BlueFire.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"

const float ENLARGE = 1.2; // when the enemy image shows up on the gameboard, it is enlarged 1.2 times.

BlueFire::BlueFire(float x, float y) : AbstractEnemy(x,y)
{
	_speed = 3.0f;
	_angle = Define::PI / 2;
	_range = 13.0 * ENLARGE;
	_health = 15;
}

bool BlueFire::update()
{
	_counter++;
	if (_y < Define::CENTER_Y - 200) {
		_x += cos(_angle) * _speed;
		_y += sin(_angle) * _speed;
	}
	return isInside();
}

void BlueFire::draw() const
{
	// draw the enemy
	const static int imgID[4] = { 0, 2, 3, 2 };
	const int handle = Image::getIns()->getBlueFire()[imgID[(_counter / 5) % 4]];
	DrawRotaGraphF(_x, _y, 1.2f, 0.0, handle, TRUE);

}

void BlueFire::setSize()
{
	int handle = Image::getIns()->getBlueFire()[0];
	GetGraphSize(handle, &_width, &_height);
}

void BlueFire::setShot()
{
	//shot01.setBullets(_x, _y, 5.0, angleEnemyAndPlayer());
}

void BlueFire::shotDraw() const 
{
}