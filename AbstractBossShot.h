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

protected:
	int _counter;
};
