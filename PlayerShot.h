#pragma once
#include "AbstractShot.h"

class PlayerShot : public AbstractShot
{
public:
	PlayerShot();
	~PlayerShot() = default;

	void setBullets(float x, float y, float angle, int power) override;
	void initBulletsAfterHittingEnemy(std::vector<int>& index);
	std::shared_ptr<AbstractShot> clone(/*std::shared_ptr<AbstractShot> base*/) override;

private:
	float _speed = 17;
	int _bulletType = 2;
	int _bulletColor = 0;
	float _range = 10.0;
	//float _range;
};