#include "GameScene.h"
#include "Error.h"
#include <DxLib.h>
#include "Background.h"
#include "HitCheck.h"

#define ERR(str) Error::finish(str, __FUNCTION__, __LINE__);

using namespace std;

const char* GameScene::ParameterTagsStage = "ParameterTagStage";
const char* GameScene::ParameterTagLevel = "ParameterTagLevel";

GameScene::GameScene(IOnSceneChangedListener* imply, const Parameter& parameter) : AbstructScene(imply, parameter)
{
	/*_level = parameter.get(ParameterTagLevel);
	if (_level == parameter.Error) {
		ERR("Nonexistent level");
	}*/
	_background = make_shared<Background>();
	_player = make_shared<Player>();
	_board = make_shared<GameBoard>();
	_enemyManager = make_shared<EnemyManager>();
	_boss = make_shared<YakumoRan>();
}

void GameScene::update()
{
	_background->update();
	//_board->update();
	_player->update();
	linkPlayerShot(); // keep updating all of the active player shots on EnemyManager class
	linkPlayerBoard();

	/* when enemyManager's flag is off, normal enemies shoudl be on the game board
	   otherwise, the stage boss should be on the game board*/
	if (_enemyManager->getFlag()) {
		_boss->update();
	}
	else {
		_enemyManager->update();
		linkEnemyShot(); // keep updating all of the active enemy shots on Player class
	}

	_board->update();
	linkPlayerEnemy(); // keep updating the player's location on EnemyManager class

	/* if the player died, give 2 options (1)go back to the title (2)play again */
	if (_player->getHealth() < 0) {
		Parameter parameter;
		//parameter.set(GameScene::ParameterTagLevel, Define::eLevel::normal);
		const bool stackClear = false;

		// use the parameter that we set above to specify next scene
		_implSceneChanged->onSceneChanged(eScene::Option, parameter, stackClear);
	}
}

void GameScene::draw() const
{
	_background->draw();
	_board->draw();
	_player->draw();
	if (_enemyManager->getFlag()) {
		_boss->draw();
	}
	else {
		_enemyManager->draw();
	}
	//_board->draw();

}

float GameScene::getPlayerX() const
{
	return _player->getX();
}

float GameScene::getPlayerY() const
{
	return _player->getY();
}

int GameScene::getPlayerPower() const
{
	return _player->getPower();
}

int GameScene::getPlayerHealth() const
{
	return _player->getHealth();
}

/* get player's location and power, and pass the value to each enemy
   use this to check if player bullets hit enemies*/
void GameScene::linkPlayerEnemy()
{
	float x = getPlayerX();
	float y = getPlayerY();
	int power = getPlayerPower();
	_enemyManager->setPlayerX(x); // save the player's location at EnemyManager Object
	_enemyManager->setPlayerY(y); // save the player's location at EnemyManager object
	_enemyManager->setPlayerPower(power); // save the player's power at EnemeyManager object
}

/* keep updating player's shot in EnemyManager class.
   Also initialize a pointer in EnemyManager class. This needs to be called _enemyManager's update*/
void GameScene::linkPlayerShot()
{
	//_enemyManager->setActivePlayerBullets(_player->getActivePlayerBullet());
	_enemyManager->setPlayerShot(_player->getPlayerShotRef());
}

/* pass all of the active enemy shots to player class.
   use this to check if the enemy shot hits the player */
void GameScene::linkEnemyShot()
{
	_player->setActiveEnemyBullets(_enemyManager->getActiveEnemyBullet());
}

void GameScene::linkPlayerBoard()
{
	_board->setPlayerProperty(getPlayerHealth(), getPlayerPower());
}