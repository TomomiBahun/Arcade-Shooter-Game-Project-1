#pragma once
#include "Singleton.h"
#include "Bullet.h"
#include <vector>

class HitCheck : public Singleton<HitCheck>
{
public:
	HitCheck() = default;
	virtual ~HitCheck() = default;

	bool didBulletHitMe(std::vector<Bullet> shot, int n, float x, float y, float range);
	bool didBulletHitMe(Bullet shot[], int n, float x, float y, float range, int player);
	std::vector<int>& getPlayerShotHitIndex() { return playerShotHitIndex; }

private:
	std::vector<int> playerShotHitIndex;
};

