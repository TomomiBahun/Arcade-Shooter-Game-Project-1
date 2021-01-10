#include "Reimu.h"
#include "Image.h"
#include "keyboard.h"
#include "Define.h"

Reimu::Reimu(int speed, int power, float range)
{
	// speed = 6, power = 1, range = 10.5
	setCharacter(speed, power, range);
}

void Reimu::draw() const
{
	if (_noHitTimer == 0) {
		DrawRotaGraphF(_x, _y, 1.8f, 0.0f, Image::getIns()->getReimu()[direction], TRUE);
		/* when slow mode, show a hit box*/
		if (_slow) {
			DrawRotaGraphF(_x, _y, 2.1f, (double)_boxAngle, Image::getIns()->getHitBox(), TRUE);
		}
	}
	else {
		if (_counter % 7 == 0) { // during no hit time, blink the player image
			DrawRotaGraphF(_x, _y, 1.8f, 0.0f, Image::getIns()->getReimu()[direction], TRUE);
			/* when slow mode, show a hit box*/
			if (_slow) {
				DrawRotaGraphF(_x, _y, 2.1f, (double)_boxAngle, Image::getIns()->getHitBox(), TRUE);
			}
		}
	}
	_playerShot.draw();
}

void Reimu::move()
{
	// change in x and y
	float moveX = 0;
	float moveY = 0;

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) > 0) {
		moveY += _speed;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) > 0) {
		moveY -= _speed;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) > 0) {
		const static int imgID[4] = { 7, 8, 9, 8 };
		int push = Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT);
		moveX -= _speed;
		if (0 < push && push < 3) {
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
		const static int imgID[4] = { 12, 13, 14, 13 };
		int push = Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT);
		moveX += _speed;
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