#pragma once
#include "Task.h"

class AbstractBoss : public Task
{
public:
	AbstractBoss();
	virtual ~AbstractBoss() = default;
	bool update() override;

protected:
	int _counter;
	float _x, _y; // player coordinate
	float _w = 50.0f; // player width
	float _h = 50.0f; // player width;
	float _range = 7.5f; // player range
	float _speed;
	float _angle;
	float _health;
	int _direction;

	/* attributes to calculate boss move*/
	int _moveCounter;
	int _moveTime;
	bool _moving;
	float _v0x;
	float _v0y;
	float _ax;
	float _ay;
	float _preX;
	float _preY;
	bool _bottom;
};
