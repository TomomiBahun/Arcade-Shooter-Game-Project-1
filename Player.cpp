#include "Player.h"
#include "keyboard.h"
#include <DxLib.h>
#include "Image.h"
#include "Define.h"
#include "ImageBullet.h"
#include "Sound.h"

using namespace std;

const static float SPEED = 6;

/* set the initial location (x, y) = (100, 100) and load the player image */
Player::Player() :
	_counter(0),
	_slow(false),
	_boxAngle(0.0),
	_x(Define::CENTER_X),
	_y(Define::CENTER_Y + 500),
	direction(0), directionCount(0),
	_power(1),
	_health(50),
	_noHitTimer(0)
{
}

bool Player::update()
{
	/* check if any of enemy bullet hits the player
	   if player gets hit, decrease the player health and set the noHitTimer*/
	if (_noHitTimer == 0) {
		if (didBulletHitMe()) {
			_noHitTimer = 12;
		}
	}
	else {
		if (_counter % 7 == 0)
			_noHitTimer--;
	}

	/* after checking all of the bullets in this frame, init the vector */
	_activeEnemyBullets.clear();
	_activeBossBullets.clear();

	/* continue rotating hitBox image*/
	if (_boxAngle <= 2*Define::PI) {
		_boxAngle += Define::PI / 180;
	}
	else {
		_boxAngle = 0.0;
	}

	_counter++;
	move();
	shotBullets();
	_playerShot.initBulletsAfterHittingEnemy(HitCheck::getIns()->getPlayerShotHitIndex());
	_playerShot.update();
	return true;
}

void Player::draw() const
{
	if (_noHitTimer == 0) {
		//DrawRotaGraphF(_x, _y, 1.5f, 0.0f, Image::getIns()->getPlayer()[direction], TRUE);
		DrawRotaGraphF(_x, _y, 1.8f, 0.0f, Image::getIns()->getReimu()[direction], TRUE);
		/* when slow mode, show a hit box*/
		if (_slow) {
			DrawRotaGraphF(_x, _y, 2.1f, (double)_boxAngle, Image::getIns()->getHitBox(), TRUE);
		}
	}
	else {
		if (_counter % 7 == 0) { // during no hit time, blink the player image
			//DrawRotaGraphF(_x, _y, 1.5f, 0.0f, Image::getIns()->getPlayer()[direction], TRUE);
			DrawRotaGraphF(_x, _y, 1.8f, 0.0f, Image::getIns()->getReimu()[direction], TRUE);
			/* when slow mode, show a hit box*/
			if (_slow) {
				DrawRotaGraphF(_x, _y, 2.1f, (double)_boxAngle, Image::getIns()->getHitBox(), TRUE);
			}
		}
	}
	_playerShot.draw();
}

/* get all of the active bullets */
std::vector<Bullet>& Player::getActivePlayerBullet()
{
	_activePlayerBullets.clear(); // before updating the vector, delete the elements from the previous frame
	for (int i = 0; i < AbstractShot::MAX_BULLETS; i++) {
		if (_playerShot.shot[i].getFlag() > 0) {
			_activePlayerBullets.push_back(_playerShot.shot[i]);
		}
	}
	return _activePlayerBullets;
}

/* get enemy's bullet information at Player class*/
void Player::setActiveEnemyBullets(std::vector<Bullet>& enemyBullets)
{
	_activeEnemyBullets.clear(); // delete all elements in vector before updating it
	for (int i = 0; i < enemyBullets.size(); i++) {
		_activeEnemyBullets.push_back(enemyBullets[i]);
	}
}

/* get boss's bullet information at Player class*/
void Player::setActiveBossBullets(std::vector<Bullet>& bossBullets)
{
	_activeEnemyBullets.clear(); // delete all elements in vector before updating it
	for (int i = 0; i < bossBullets.size(); i++) {
		_activeBossBullets.push_back(bossBullets[i]);
	}
}

/* controls player's location and move*/
void Player::move()
{
	// change in x and y
	float moveX = 0;
	float moveY = 0;
	
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) > 0) {
		moveY += SPEED;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) > 0) {
		moveY -= SPEED;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) > 0) {
		const static int imgID[4] = { 7, 8, 9, 8 };
		int push = Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT);
		moveX -= SPEED;
		if (0 < push && push < 3){
			direction = 6;
		}
		else if (2 < push && push < 5) {
			direction = 7;
		}
		else if (4 < push && push < 7) {
			direction = 8;
		}
		else {
			direction = imgID[(_counter / 8) % 4];
		}
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) > 0) {
		const static int imgID[4] = { 12, 13, 14, 13};
		int push = Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT);
		moveX += SPEED;
		if (0 < push && push < 3) {
			direction = 11;
		}
		else if (2 < push && push < 5) {
			direction = 12;
		}
		else if (4 < push && push < 7) {
			direction = 13;
		}
		else {
			direction = imgID[(_counter / 8) % 4];
		}
	}

	 /* Adjust the player's move speed, when moving diagonally */
	if (moveX && moveY) {
		moveX /= (float)sqrt(2.0);
		moveY /= (float)sqrt(2.0);
	}

	/* When Left Shit key is pushed, enable Slow-move mode */
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LSHIFT) > 0) {
		moveX /= 3;
		moveY /= 3;
		_slow = true; // change the state of the slow-move mode
	}
	else {
		_slow = false;
	}

	/* if no horizontal move, set the direction back to normal */
	if (moveX == 0) {
		const static int imgID[8] = { 0, 1, 2, 3, 4, 3, 2, 1 };
		direction = imgID[(_counter / 8) % 8];
	}
	
	/* Limit the movable area for the player */
	if (moveX + _x < Define::IN_X + (_w / 2)) { // if beyond the left side of game board
		_x = (float)(Define::IN_X + (_w / 2));
	}
	else if (moveX + _x > Define::IN_X + Define::INNER_W - (_w / 2)) { // if beyond the right side of game board
		_x = (float)(Define::IN_X + Define::INNER_W - (_w / 2));
	}
	else { // if within the game board
		_x += moveX;
	}
	if (moveY + _y < Define::IN_Y + (_h / 2)) { // if beyond the game board
		_y = (float)(Define::IN_Y + (_h / 2));
	}
	else if (moveY + _y > Define::IN_Y + Define::INNER_H - (_h / 2)) { // if beyond the bottom of the game board
		_y = (float)(Define::IN_Y + Define::INNER_H - (_h / 2));
	}
	else { // if within the game board
		_y += moveY;
	}
}

/* Player's shot properties */
void Player::shotBullets()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) > 0) {
		/* when Slow-move mode, bullets are closer to center. */
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LSHIFT) > 0) {
			_playerShot.setBullets(_x + 15, _y - 8, Define::PI / 2 * 3, _power);
			_playerShot.setBullets(_x - 15, _y - 8, Define::PI / 2 * 3, _power);
		}
		else {
			_playerShot.setBullets(_x + 25, _y - 8, Define::PI / 2 * 3, _power);
			_playerShot.setBullets(_x - 25, _y - 8, Define::PI / 2 * 3, _power);
		}
	}
}

/* Check if enemy's bullet hits the player.
   This function can become very expensive easily, because there can be so many bullets on the screen.
   Check only the area around the player...
   _x-100 < check area < _x+100, _y-100 < check area < _y+100 */
bool Player::didBulletHitMe()
{
	for (int i = 0; i < _activeEnemyBullets.size(); i++) {
		if (_y - 100 < _activeEnemyBullets[i].getY() && _activeEnemyBullets[i].getY() < _y + 100) {
			if (_x < _activeEnemyBullets[i].getX() && _activeEnemyBullets[i].getX() < _x + 100) {
				if (HitCheck::getIns()->didBulletHitPlayer(_activeEnemyBullets, i, _x, _y, _range)) {
					_health -= 10; // all enemy bullets power are 10
					PlaySoundMem(Sound::getIns()->getGetHitSound(), DX_PLAYTYPE_BACK); // play hit sound
					return true;
				}
			}
		}
	}

	for (int i = 0; i < _activeBossBullets.size(); i++) {
		if (_y - 100 < _activeBossBullets[i].getY() && _activeBossBullets[i].getY() < _y + 100) {
			if (_x < _activeBossBullets[i].getX() && _activeBossBullets[i].getX() < _x + 100) {
				if (HitCheck::getIns()->didBulletHitPlayer(_activeBossBullets, i, _x, _y, _range)) {
					_health -= 10; // all enemy bullets power are 10
					PlaySoundMem(Sound::getIns()->getGetHitSound(), DX_PLAYTYPE_BACK); // play hit sound
					return true;
				}
			}
		}
	}
	return false;
}