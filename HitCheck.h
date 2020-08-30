#pragma once
#include "Singleton.h"
#include "Bullet.h"
#include <vector>

class HitCheck : public Singleton<HitCheck>
{
public:
	HitCheck() = default;
	virtual ~HitCheck() = default;

	bool didBulletHitPlayer(std::vector<Bullet> shot, int n, float x, float y, float range);
	bool didBulletHitEnemy(Bullet shot[], int n, float x, float y, float range);
	std::vector<int>& getPlayerShotHitIndex();
	void clearPlayerShotHitIndex();

private:
	std::vector<int> playerShotHitIndex;
};

