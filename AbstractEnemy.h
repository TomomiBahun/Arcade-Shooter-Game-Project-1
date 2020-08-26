#pragma once
#include "Task.h"

/* pure virtual */
class AbstractEnemy : public Task
{
public:
	AbstractEnemy(float x, float y);
	virtual ~AbstractEnemy() = default;
	void initialize();
	bool update() override;

	float getX() const { return _x; }
	float getY() const { return _y; }
	float getRange() const { return _range; }
	int getHealth() const { return _health; }
	void updateHealth(int playerPower);
	//void setPlayerX(float x) { _playerX = x; };
	//void setPlayerY(float y) { _playerY = y; };
	//float angleEnemyAndPlayer() const;

protected:
	virtual void setSize() = 0;
	bool isInside() const;

	float _x, _y;
	float _speed;
	float _angle;
	float _range;

	int _counter;
	int _width;
	int _height;
	int _health;
};

