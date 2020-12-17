#pragma once
#include "Singleton.h"
#include <vector>

class Sound final: public Singleton<Sound>
{
public:
	Sound();
	~Sound() = default;
	void load() {}
	void release();

	/* getters */
	int const getHitSound() { return _hit; }
	int const getEnemyShotSound() { return _enemyShot; }
	int const getBulletEffectSound() { return _bulletEffect; }
	int const getSpellCardEffectSound() { return _spellCardEffect; }
	int const getBossDefeatSound() { return _bossDefeat; }
	int const getGetHitSound() { return _getHit; }
	int const getTitleSound() { return _title; }
	int const getStage1Sound() { return _stage1; }
	int const getStage1BossSound() { return _stage1Boss; }

private:
	std::vector<int> _sound;
	int myLoadSound(const char*);

	/* variables for sound*/
	int _hit;
	int _enemyShot;
	int _bulletEffect;
	int _spellCardEffect;
	int _bossDefeat;
	int _getHit;
	int _title;
	int _stage1;
	int _stage1Boss;
};

