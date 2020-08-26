#pragma once
#include "Task.h"

class Bullet : public Task
{
public:
	Bullet();
	Bullet(float x, float y, float speed, float angle, int flag, int power, int bulletType, int bulletColor);
	virtual ~Bullet() = default;
	bool update() override;
	void draw() const override;

	int getFlag() const;
	float getX() const { return _x; }
	float getY() const { return _y; }
	float getSpeed() const { return _speed; }
	float getAngle() const { return _angle; }
	float getRange() const { return _range; }
	void setFlag(int flag);
	void setBullet(float x, float y, float speed, float angle, int power, int bulletType, int bulletColor);
	void setRange();

	void initBullet();

protected:
	bool isInside() const;

	float _x, _y;
	float _speed;
	float _angle;
	int _counter;
	mutable int _flag; // temporarily mutable
	int _power; // power is defined for the player's shot. for enemy's shot, set a dummy value.
	int _bulletType;
	int _bulletColor;
	float _range;
};

