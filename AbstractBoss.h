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

	/* getters & setters for Boss status*/
	bool getBossShotStatus() { return _canBossStartBullets; } // returns boss shot status
	bool getBossPresenceStatus() { return _canBossCome; } // return boss status (is boss on the game board?)
	bool getBossConversationStatus() { return _isBossTalking; } // return boss conversation status
	float getBossHealth() { return _health; }
	float getBossHealthMax() { return _healthMax; }
	void setBossShotStatus(bool answer) { _canBossStartBullets = answer; _counter = 0; } // this is to set boss status at GameScene class
	void setBossPresenceStatus(bool answer) { _canBossCome = answer; } // this is to set boss status at GameScene class
	void setBossConversationStatus(bool answer) { _isBossTalking = answer; } // set conversation status

	/* setters for receiving the player's status*/
	void setPlayerX(float x) { _playerX = x; } // this receives player information from GameScene class
	void setPlayerY(float y) { _playerY = y; } // this receives player inforamtion from GameScene class
	void setPlayerPower(int power) { _playerPower = power; } // this receives player informaiont from GameScene class
	void setPlayerShot(AbstractShot& shot); // receives Player's shot reference to do hit-check at Boss class

protected:
	/* functions to do hit-check and get related angles*/
	float angleBossAndPlayer();
	float angleBossAndDestination();
	bool didBulletHitMe();

	/* functions to control boss move and health*/
	void inputDestinationAndTime(int t, float xDest, float yDest);
	void moveBoss();
	void moveUpDown(); // stay at the base potision, but keep moving
	bool updateCircle();
	void drawHealth() const;
	void drawCircle() const;

	/* attributes to control moss in general*/
	int _counter;
	float _x, _y; // boss coordinate
	float _w = 50.0f; // boss width
	float _h = 50.0f; // boss width;
	float _range; // boss range
	float _speed;
	float _angle;
	float _health;
	float _healthMax;
	bool _moveToLoc;
	int _upDownCount;

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
	bool _isBossTalking;

	/* attributes to control boss shot */
	std::vector<std::shared_ptr<AbstractBossShot>> shots; // holding boss shots
	int _shotIndex; // index for different kinds of shots

	/* attributes to keep player's info*/
	AbstractShot* playerShot; // receives player's shot to do hit-check at Boss class
	float _playerX, _playerY;
	int _playerPower;

	/* attributes to keep boss's info on other class*/
	std::vector<Bullet> _activeBossBullets; // this is to pass all active boss bullets to Player class

	/* attributes to control decorations */
	float _circleAngle;
	float _circleExpand;
	int _shrinkOrEnlarge; // 0: Enlarge fast, 1: Enlarge slow, 2: shrink slow
};

