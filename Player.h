#pragma once
#include "Task.h"
#include "HitCheck.h"
#include "PlayerShot.h"
#include "AbstractBossShot.h"

/* child class of Task*/
class Player : public Task
{
public:
	Player();
	virtual ~Player() = default;
	bool update() override;
	void draw() const override;
	float getX() const { return _x; }
	float getY() const { return _y; }
	int getPower() const { return _power; }
	int getHealth() const { return _health; }
	std::vector<Bullet>& getActivePlayerBullet();
	PlayerShot& getPlayerShotRef() { return _playerShot; } // pass ref of _playerShot to EnemyManager and boss class for their hit-check
	void setActiveEnemyBullets(std::vector<Bullet>& enemyBullets); // use this to do hit-check
	void setActiveBossBullets(std::vector<Bullet>& bossBullets); // use this to do hit-check

private:
	PlayerShot _playerShot; // player's bullets
	std::vector<Bullet> _activePlayerBullets; // this is to pass all active player's bullets to the enemy class
	std::vector<Bullet> _activeEnemyBullets; // this is to check if enemy's bullets hit the player
	std::vector<Bullet> _activeBossBullets; // this is to check if boss's bullet's hit the player

	int _counter;
	bool _slow;
	float _boxAngle;
	float _x, _y; // player coordinate
	float _w = 50.0f; // player width
	float _h = 50.0f; // player width;
	float _range = 10.5f; // player range
	int direction;
	int directionCount;
	int _power;
	int _health;
	int _noHitTimer;

	void move();
	void shotBullets();
	bool didBulletHitMe();
};

