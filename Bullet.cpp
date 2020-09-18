#include "Bullet.h"
#include "ImageBullet.h"
#include "Define.h"
#include <DxLib.h>

Bullet::Bullet() :
	_x(0.0),
	_y(0.0),
	_speed(0.0),
	_angle(0.0),
	_counter(0),
	_flag(0),
	_power(0),
	_bulletType(0),
	_bulletColor(0)
{
}

Bullet::Bullet(float x, float y, float speed, float angle, int flag, int power, int bulletType, int bulletColor) : 
	_x(x), 
	_y(y),
	_speed(speed),
	_angle(angle),
	_counter(0),
	_flag(flag),
	_power(power),
	_bulletType(bulletType),
	_bulletColor(bulletColor)
{
}

bool Bullet::update()
{
	_counter++;
	_x += cos(_angle) * _speed;
	_y += sin(_angle) * _speed;
	return true;
}

void Bullet::draw() const
{
	if (isInside() == true) {
		DrawRotaGraphF(_x, _y, 1.6f, _angle + Define::PI/2, ImageBullet::getIns()->getImage(static_cast<ImageBullet::eBulletType>(_bulletType), static_cast<ImageBullet::eBulletColor>(_bulletColor)), TRUE);
	}
}

int Bullet::getFlag() const
{
	return _flag;
}

void Bullet::setFlag(int flag)
{
	_flag = flag;
}

void Bullet::setBullet(float x, float y, float speed, float angle, int power, int bulletType, int bulletColor)
{
	_x = x;
	_y = y,
	_speed = speed;
	_angle = angle;
	_power = power; // power is defined to control the player's shot. For enemy's shot, set a dummy value.
	_bulletType = bulletType;
	_bulletColor = bulletColor;
	_range = ImageBullet::getIns()->getRange(bulletType);
}

void Bullet::setRange()
{
	//_range = ImageBullet::RANGE[_bulletType];
}

void Bullet::initBullet()
{
	_x = 0.0;
	_y = 0.0;
	_angle = 0.0;
	_power = 0;
	_counter = 0;
	_flag = 0;
	_range = 0.0;
}

bool Bullet::isInside() const
{
	if (_counter < 60) {
		return true;
	}

	// ******************** Maybe I should let the bullets move beyond the boarders a bit *****************
	/* bullet's size and gameboard border*/
	float bulletWidth = (float)ImageBullet::getIns()->getSize(_bulletType)->getWidth();
	float bulletHeight = (float)ImageBullet::getIns()->getSize(_bulletType)->getHeight();
	float leftBorder = Define::IN_X + (bulletWidth / 2);
	float rightBorder = Define::IN_X + Define::INNER_W - (bulletWidth / 2);
	float upperBorder = Define::IN_Y;
	float bottomBorder = Define::IN_Y + Define::INNER_H - (bulletHeight / 2);

	if (_x < leftBorder || rightBorder < _x || _y < upperBorder || bottomBorder < _y) {
		_flag = 0; // temporarily mutable
		return false;
	}
	return true;
}

// bool Bullet::isAvailable() const