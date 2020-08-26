#pragma once
#include "Task.h"
#include "HitCheck.h"
#include "PlayerShot.h"

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
	PlayerShot getPlayerShot() const { return _playerShot; }
	std::vector<Bullet>& getActivePlayerBullet();
	PlayerShot& getPlayerShotRef() { return _playerShot; }
	void setActiveEnemyBullets(std::vector<Bullet>& enemyBullets); // use this to hit check
	void setToBeDeletedBullets(std::vector<int>& playerShotIndex) { _playerShotIndex = playerShotIndex; }

private:
	PlayerShot _playerShot; // player's bullets
	std::vector<Bullet> _activeEnemyBullets; // this is to check if enemy's bullets hit the player
	std::vector<Bullet> _activePlayerBullets; // this is to pass all active player's bullets to the enemy class
	std::vector<int> _playerShotIndex;

	int _counter;
	float _x, _y; // player coordinate
	float _w = 50.0f; // player width
	float _h = 50.0f; // player width;
	float _range = 25.0f; // player range
	int direction;
	int _power;
	int _health;
	mutable int _noHitTimer; // temporarily mutable
	int _image[6]; // place holder for the image

	void move();
	void shotBullets();
	bool didBulletHitMe();
};

