#pragma once
#include "Task.h"
#include <memory>
#include <vector>
#include "Bullet.h"
#include "AbstractEnemy.h"
#include "AbstractShot.h"
#include <algorithm> // for copy()
#include <iterator> // for back_inserter 


class EnemyManager : public Task
{
public:

	const static int ENEMY_SHOT_POWER = 10;

	EnemyManager();
	virtual ~EnemyManager() = default;
	bool update() override;
	void draw() const override;

	std::vector<Bullet>& getActiveEnemyBullet();
	std::vector<std::shared_ptr<AbstractEnemy>>& getList() { return _list; }
	bool getFlag() const { return _flag; }
	void setPlayerX(float x) { _playerX = x; }
	void setPlayerY(float y) { _playerY = y; }
	void setPlayerPower(int power) { _playerPower = power; }
	void setPlayerShot(AbstractShot& shot); // receives Player's shot reference to do hit-check at EnemyManager class

	float angleEnemyAndPlayer(float enemyX, float enemyY) const;

private:
	bool _flag; // when true, boss should appear on the game board
	int _count;
	float _playerX, _playerY;
	int _playerPower;
	AbstractShot* playerShot; // receives player's shot to do hit-check at EnemyManager class
	std::vector<Bullet> _activeEnemyBullets; // this is to pass all active enemy bullets to Player class
	std::vector<std::shared_ptr<AbstractEnemy>> _list; // enemy's list
	std::vector<std::shared_ptr<AbstractShot>> _shotList; // alive enemy's shot list
	std::vector<std::shared_ptr<AbstractShot>> _continueShotList; // even after enemy dies, bullets on the board need to keep moving. 

	bool didBulletHitMe(std::shared_ptr<AbstractEnemy> Enemy);
	void loadEnemyAndShots();
};