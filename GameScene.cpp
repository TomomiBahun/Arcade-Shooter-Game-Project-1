#include "GameScene.h"
#include "Error.h"
#include <DxLib.h>
#include "Background.h"
#include "keyboard.h"
#include "HitCheck.h"
#include "Sound.h"

#define ERR(str) Error::finish(str, __FUNCTION__, __LINE__);

using namespace std;

const char* GameScene::ParameterTagsStage = "ParameterTagStage"; // used when specifying stage
const char* GameScene::ParameterTagCharacter = "ParameterTagCharacter"; // used when specifying character

GameScene::GameScene(IOnSceneChangedListener* imply, const Parameter& parameter) : AbstructScene(imply, parameter)
{
	/*_level = parameter.get(ParameterTagLevel);
	if (_level == parameter.Error) {
		ERR("Nonexistent level");
	}*/
	_background = make_shared<Background>();
	//_player = make_shared<Player>();
	_board = make_shared<GameBoard>();
	_enemyManager = make_shared<EnemyManager>();
	_boss = make_shared<YakumoRan>();

	// use Reimu or Marisa depending on the Parameter
	if (parameter.get(ParameterTagCharacter) == 1) {
		_currentCharacter = 1;
		_player = make_shared<Reimu>(6, 1, 10.5);
		_conversation = make_shared<S1ReimuConversation>();
		_endConversation = make_shared<S1ReimuEndConversation>();
	}
	else {
		_currentCharacter = 2;
		_player = make_shared<Marisa>(8, 2, 11.0);
		_conversation = make_shared<S1MarisaConversation>();
		_endConversation = make_shared<S1MarisaEndConversation>();
	}
}

void GameScene::update()
{
	_background->setBossBackStatus(_boss->getBossBackStatus());
	_background->update();
	_player->update();
	linkPlayerShotAndEnemy(); // keep updating all of the active player shots on EnemyManager class
	linkPlayerBoard();

	/* when enemyManager's flag is off, normal enemies should be on the screen
	   otherwise, the stage boss should be on the screen*/

	/* while boss is on the screen (no regular enemies) */
	if (_enemyManager->getFlag()) {

		if (!_boss->getIsStageVer()) {
			// keep setting new boss bullets... when conversation is over & boss's shot status is ON
			if (_boss->getBossHealth() == _boss->getBossHealthMax()) {
				if (!_conversation->update() && !_boss->getBossShotStatus()) {
					_boss->setBossConversationStatus(false);
					_boss->setBossShotStatus(true);
				}
			}

			// let the boss show up on the game screen... when conversation is at certain point
			if (_conversation->getBoss()) {
				linkPlayerShotAndBoss();
				_boss->update(); // boss need to keep moving regardless of the scene
				if (!CheckSoundMem(Sound::getIns()->getStage1BossSound())) {
					StopSoundMem(Sound::getIns()->getStage1Sound());
					PlaySoundMem(Sound::getIns()->getStage1BossSound(), DX_PLAYTYPE_LOOP);
					//isSoundOn = true;
				}
			}

			// Keep updating shots and location info on boss and player classes... when boss's shot status is ON
			if (_boss->getBossShotStatus()) {
				linkBossShotAndPlayer();
				linkPlayerBoss();
			}
		}
		else { // when player beats the stage boss
			_endConversation->update();
		}
	}
	else { /* while regular enemies are on the game screen*/
		_enemyManager->update();
		linkEnemyShotAndPlayer(); // keep updating all of the active enemy shots on Player class
		linkPlayerEnemy(); // keep updating the player's location on EnemyManager class
		if (!CheckSoundMem(Sound::getIns()->getStage1Sound())) {
			PlaySoundMem(Sound::getIns()->getStage1Sound(), DX_PLAYTYPE_LOOP);
		}
	}

	_board->update();

	/* Scene Changes - the player dies & the player defeats the stage boss */
	if (_player->getHealth() < 0) {
		// Stop Music
		StopSoundMem(Sound::getIns()->getStage1Sound());
		StopSoundMem(Sound::getIns()->getStage1BossSound());

		// if the player died, give 2 options (1)go back to the title (2)play again
		Parameter parameter;
		parameter.set(GameScene::ParameterTagCharacter, _currentCharacter);
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Option, parameter, stackClear);
	}
	else if (_endConversation->getFlag()) {
		// if the player hits the speficic key
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {
			// stop the sound first
			StopSoundMem(Sound::getIns()->getStage1BossSound());

			// go back to the title screen
			Parameter parameter;
			const bool stackClear = true;
			_implSceneChanged->onSceneChanged(eScene::Menu, parameter, stackClear);
		}
	}

}

void GameScene::draw() const
{
	_background->draw();
	_player->draw();
	if (_enemyManager->getFlag()) {
		if (!_boss->getIsStageVer()) {
			if (!_boss->getBossShotStatus() && _boss->getBossConversationStatus()) {
				_conversation->draw();
			}
			if (_conversation->getBoss()) { // when conversation is at a certain point, let the boss come in game board
				_boss->draw();
			}
		}
		else {
			_endConversation->draw();
		}
	}
	else {
		_enemyManager->draw();
	}
	_board->draw();

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

void GameScene::linkPlayerBoss()
{
	float x = getPlayerX();
	float y = getPlayerY();
	int power = getPlayerPower();
	_boss->setPlayerX(x); // save the player's location at boss Object
	_boss->setPlayerY(y); // save the player's location at boss object
	_boss->setPlayerPower(power); // save the player's power at boss object
}

/* keep updating player's shot in EnemyManager class. Also initialize a pointer in EnemyManager class.
   This needs to be called before _enemyManager's update */
void GameScene::linkPlayerShotAndEnemy()
{
	_enemyManager->setPlayerShot(_player->getPlayerShotRef());
}

/* keep updating player's shot in Boss class. Also initialize a pointer in EnemyManager class.
   This needs to be called _boss's update. This shouldn't be called before conversation is done */
void GameScene::linkPlayerShotAndBoss()
{
	_boss->setPlayerShot(_player->getPlayerShotRef());
}

/* pass all of the active enemy shots to player class.
   use this to check if the enemy shot hits the player */
void GameScene::linkEnemyShotAndPlayer()
{
	_player->setActiveEnemyBullets(_enemyManager->getActiveEnemyBullet());
}

/* pass all of the active boss shots to player class.
   use this to check if the boss shot hits the player */
void GameScene::linkBossShotAndPlayer()
{
	_player->setActiveBossBullets(_boss->getActiveBossBullet(_boss->getShotIndex()));
}

void GameScene::linkPlayerBoard()
{
	_board->setPlayerProperty(getPlayerHealth(), getPlayerPower());
}