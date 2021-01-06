#include "EnemyManager.h"
#include "Define.h"
#include "Image.h"
#include "BlueFire.h"
#include "GreenFire01.h"
#include "GreenFire02.h"
#include "Shot01.h"
#include "Shot02.h"
#include "Shot03.h"
#include "HitCheck.h"
#include <DxLib.h>

using namespace std;

const static int MAX_BRIGHTNESS = 255;

/* This class holds each enemy object in the list */
EnemyManager::EnemyManager() : _count(0), _flag(false), _titleBrightness(0), _titleCount(0)
{
}

bool EnemyManager::update()
{
	/* always update the count and and load Enemy&Shots info first*/
	_count++;
	loadEnemyAndShots();

	/* clear playerShotHitIndex from the last frame */
	HitCheck::getIns()->clearPlayerShotHitIndex();

	/* keep updating the enemies in _list.
	   If enemy gets out of the game board OR enemy health is 0, erase the enemy object from the _list.
	   Also enemy will keep shooting bullets while they are inside the game board*/
	int backwards;
	for (int i = 0; i < _list.size(); i++) {
		if (_list[i]->update() == false || didBulletHitMe(_list[i]) == false) {
			backwards = _shotList.size() - (i + 1) ;
			// enemy died or moved out of the game board. Get a copy of remainig shot and keep updating them
			copy(_shotList.begin()+i, _shotList.end() - backwards, back_inserter(_continueShotList)); // insert at the end of vector
			_list.erase(_list.begin()+ i);
			_shotList.erase(_shotList.begin() + i);
		}
		else { // if the enemy is still on the game board, keep setting a bullet
			float currentAngle = angleEnemyAndPlayer(_list[i]->getX(), _list[i]->getY());
			_shotList[i]->setBullets(_list[i]->getX(), _list[i]->getY(), currentAngle, ENEMY_SHOT_POWER);
		}

	}

	for (int i = 0; i < _shotList.size(); i++) {
		_shotList[i]->update();
	}

	/* keep updating the bullets remaining on the game board after enemy died.
	   Even after enemy dies, bullets need to keep moving.*/
	for (int i = 0; i < _continueShotList.size(); i++) {
     		_continueShotList[i]->update();
	}

	/* update the stage title brightness*/
	if (600 < _count && _count < 900) {
		_titleCount++;
		if (600 < _count && _count < 700) { // 600<_count<700 logo appears
			_titleBrightness += 3;
			if (_titleBrightness > 255) {
				_titleBrightness = 255;
			}
		}
		else if (700 <= _count && _count < 800) { // 700<=_count<800 logo stays

		}else{ // 800<=_count<850 logo dissapears
			_titleBrightness -= 3;
			if (_titleBrightness < 0) {
				_titleBrightness = 0;
			}
		}
	}

	return true;
}

void EnemyManager::draw() const
{
	DrawFormatString(0, 20, GetColor(255, 255, 255), "The num of enemy = %d", _list.size());
	for (const auto enemy : _list) {
		enemy->draw();
	}
	for (const auto shot : _shotList) {
		shot->draw();
	}

	for (const auto shot : _continueShotList) {
		shot->draw();
	}

	// draw stage title
	if (600 < _count && _count < 900) {
		SetDrawBright(_titleBrightness, _titleBrightness, _titleBrightness);
		DrawRotaGraph(Define::CENTER_X - 100, Define::CENTER_Y, 0.9, 0.0, Image::getIns()->getStage1(), TRUE); // draw "Stage1"
		DrawRotaGraph(Define::CENTER_X + 100 + (_titleCount*0.1), Define::CENTER_Y + 60, 0.7, 0.0, Image::getIns()->getStage1Title(), TRUE); // draw "Location"
		SetDrawBright(MAX_BRIGHTNESS, MAX_BRIGHTNESS, MAX_BRIGHTNESS);
	}

}

/* get all of the active bullets */
std::vector<Bullet>& EnemyManager::getActiveEnemyBullet()
{
	_activeEnemyBullets.clear(); // before updating the vector, delete the elements from the previous frame
	for (int i = 0; i < _shotList.size(); i++) {
		for (int j = 0; j < AbstractShot::MAX_BULLETS; j++) {
			if (_shotList[i]->shot[j].getFlag() > 0) {
				_activeEnemyBullets.push_back(_shotList[i]->shot[j]);
			}
		}
	}

	return _activeEnemyBullets;
}

/*void EnemyManager::setActivePlayerBullets(std::vector<Bullet>& playerBullets)
{
	_activePlayerBullets.clear(); // delete all elements in vector before updating it
	for (int i = 0; i < playerBullets.size(); i++) {
		_activePlayerBullets.push_back(playerBullets[i]);
	}
}*/

float EnemyManager::angleEnemyAndPlayer(float enemyX, float enemyY) const
{
	return atan2(_playerY - enemyY, _playerX - enemyX);
}

/* check if player's bullet hit enemy
   return false if enemy is dead after this frame. return true if enemy is still alive.*/
bool EnemyManager::didBulletHitMe(std::shared_ptr<AbstractEnemy> enemy)
{
	for (int i = 0; i < playerShot->MAX_BULLETS; i++) {
		if (playerShot->shot[i].getFlag() > 0) {
			if (HitCheck::getIns()->didBulletHitEnemy(playerShot->shot, i, enemy->getX(), enemy->getY(), enemy->getRange())) {
				enemy->updateHealth(_playerPower); // decrease enemy health
				if (enemy->getHealth() <= 0) {
					return false; // enemy is dead!
				}
			}
		}
	}
	return true;
}

/* get player's shot from GameScene class to check if bullets hit the enemy*/
void EnemyManager::setPlayerShot(AbstractShot& shot)
{
	playerShot = &shot;
}

void EnemyManager::loadEnemyAndShots()
{
	// One shot type per regular enemy. Total num of _list = Total num of _shotList
	if (_count == 200) { // 1
		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}
	
	if (_count == 241) { // 2
		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}

	if (_count == 281) { // 3
		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}

	if (_count == 321) { // 4
		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}

	if (_count == 361) { // 5
		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}
	
	if (_count == 401) { // 1
		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}

	if (_count == 441) { // 2
		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}

	if (_count == 481) { // 3
		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}

	if (_count == 521) { // 4
		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}

	if (_count == 561) { // 5
		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}


	if (_count == 700) {
		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());

		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 250, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot01>());
	}
	
	if (_count == 800) {
		_list.emplace_back(make_shared<BlueFire>(Define::CENTER_X - 100, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot03>());

		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 100, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot02>());
	}

	if (_count == 900) {
		_list.emplace_back(make_shared<BlueFire>(Define::CENTER_X + 100, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot03>());

		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X +50, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot02>());
	}

	if (_count == 951) {
		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X + 180, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot02>());

		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 150, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot02>());
	}

	if (_count == 1000) {
		_list.emplace_back(make_shared<GreenFire01>(Define::CENTER_X - 50, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot02>());

		_list.emplace_back(make_shared<GreenFire02>(Define::CENTER_X - 100, Define::IN_Y));
		_shotList.emplace_back(make_shared<Shot02>());
	}
	
	if (_count == 1450) {
		_flag = true;
	}

	/* get width and height of enemy in enemy->initialize() */
	for (auto enemy : _list) {
		enemy->initialize();
	}
}