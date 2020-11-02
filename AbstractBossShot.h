#pragma once
#include "Task.h"
#include "Bullet.h"
#include <memory>
#include <vector>

class AbstractBossShot : public Task
{
public:
	const static int MAX_BULLETS = 800;
	Bullet shot[MAX_BULLETS]; // set the initial location in the constructor

	AbstractBossShot();
	virtual ~AbstractBossShot() = default;
	bool update() override;
	void draw() const override;

	int isBulletAvailable() const;
	virtual void setBullets(float x, float y, float angle, int power) = 0;
	int getMovePattern() { return _movePattern; }
	float getMoveX() { return _moveX; }
	float getMoveY(){ return _moveY; }
	int getMoveTime() { return _moveTime; }


protected:
	int _counter;
	int _movePattern; // 0: stay at the base position, 1: move up&down, 2: move to specific loc(set _moveX & _moveY), 3: combination 1&2
	float _moveX;
	float _moveY;
	int _moveTime;
	float _angle;
	float _angle02;
};
