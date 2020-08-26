#include "GreenFire.h"
#include <DxLib.h>
#include "Image.h"
#include "Define.h"

GreenFire::GreenFire(float x, float y) : AbstractEnemy(x, y)
{
	_speed = 2.0f;
	_angle = Define::PI / 2 + Define::PI / 5;
	_range = 13.0f;
	_health = 200;
}

void GreenFire::draw() const
{
	const static int imgID[4] = { 0, 2, 3, 2 };
	const int handle = Image::getIns()->getGreenFire()[imgID[(_counter / 5) % 4]];
	DrawRotaGraphF(_x, _y, 1.2f, 0.0, handle, TRUE);
}

void GreenFire::setSize()
{
	int handle = Image::getIns()->getGreenFire()[0];
	GetGraphSize(handle, &_width, &_height);
}