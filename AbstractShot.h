#pragma once
#include "Task.h"
#include "Bullet.h"
#include <memory>
#include <vector>

class AbstractShot : public Task
{
public:
	const static int MAX_BULLETS = 150;
	Bullet shot[MAX_BULLETS]; // set the initial location in the constructor

	AbstractShot();
	virtual ~AbstractShot() = default;
	//~AbstractShot();
	bool update() override;
	void draw() const override;

	int isBulletAvailable() const;
	virtual void setBullets(float x, float y, float angle, int power) = 0;
	virtual std::shared_ptr<AbstractShot> clone(/*std::shared_ptr<AbstractShot> base*/) = 0;
	//void setRange(float range);

protected:
	int _counter;
	//float _range;
};