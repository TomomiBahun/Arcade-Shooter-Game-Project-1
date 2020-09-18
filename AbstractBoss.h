#pragma once
#include "Task.h"
#include "AbstractShot.h"
#include "AbstractBossShot.h"
#include <vector>

class AbstractBoss : public Task
{
public:
	AbstractBoss();
	virtual ~AbstractBoss() = default;
	bool update() override;
	int getShotIndex() { return _shotIndex; } // returns the current shotIndex
	std::vector<Bullet>& getActiveBossBullet(int shotIndex);
	bool getBossShotStatus() { return _canBossStartBullets; } // returns boss shot status
	bool getBossPresenceStatus() { return _canBossCome; } // return boss status (is boss on the game board?)
	void setBossShotStatus(bool answer) { _canBossStartBullets = answer; _counter = 0; } // this is to set boss status at GameScene class
	void setBossPresenceStatus(bool answer) { _canBossCome = answer; } // this is to set boss status at GameScene class
	void setPlayerX(float x) { _playerX = x; } // this receives player information from GameScene class
	void setPlayerY(float y) { _playerY = y; } // this receives player inforamtion from GameScene class
	void setPlayerPower(int power) { _playerPower = power; } // this receives player informaiont from GameScene class
	void setPlayerShot(AbstractShot& shot); // receives Player's shot reference to do hit-check at Boss class

protected:
	float angleBossAndPlayer();
	float angleBossAndDestination();
	bool didBulletHitMe();

	int _counter;
	float _x, _y; // boss coordinate
	float _w = 50.0f; // boss width
	float _h = 50.0f; // boss width;
	float _range; // boss range
	float _speed;
	float _angle;
	float _health;
	float _healthMax;
	int _direction;

	/* attributes to calculate boss move*/
	int _moveCounter; // progress(time) of one move
	int _moveTime; // the total time to spend for moving "place a" to "place b"
	bool _moving; // when true, boss is moving between points specified. New destination shouldn't be set.
	float _v0x;
	float _v0y;
	float _ax;
	float _ay;
	float _preX;
	float _preY;
	bool _bottom;

	/* attributes to control scenes*/
	bool _canBossStartBullets; // when true, boss starts its bullets
	bool _canBossCome; // when true, boss appears on the game board

	/* attributes to control boss shot */
	std::vector<std::shared_ptr<AbstractBossShot>> shots;
	int _shotIndex; // index for different kinds of shots

	/* attributes to keep player's info*/
	AbstractShot* playerShot; // receives player's shot to do hit-check at Boss class
	float _playerX, _playerY;
	int _playerPower;

	/* attributes to keep boss's info on other class*/
	std::vector<Bullet> _activeBossBullets; // this is to pass all active boss bullets to Player class
};

