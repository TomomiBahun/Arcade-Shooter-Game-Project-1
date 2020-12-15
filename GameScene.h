#pragma once
#include "AbstractScene.h"
#include <memory>
#include "Player.h"
#include "GameBoard.h"
#include "AbstractBackground.h"
#include "EnemyManager.h"
#include "YakumoRan.h"
#include "Conversation.h"
#include "SpellCardEffect.h"
#include "EndConversation.h"

class GameScene : public AbstructScene
{
public:
	const static char* ParameterTagsStage;
	const static char* ParameterTagLevel;

	// constructor
	GameScene(IOnSceneChangedListener* imply, const Parameter& parameter);

	// destructor
	virtual ~GameScene() = default;

	void update() override;
	void draw() const override;
	float getPlayerX() const;
	float getPlayerY() const;
	int getPlayerPower() const;
	int getPlayerHealth() const;

private:
	//int _level;
	std::shared_ptr<Player> _player;
	std::shared_ptr<GameBoard> _board;
	std::shared_ptr<AbstractBackground> _background;
	std::shared_ptr<EnemyManager> _enemyManager;
	std::shared_ptr<AbstractBoss> _boss;
	std::shared_ptr<Conversation> _conversation;
	std::shared_ptr<EndConversation> _endConversation;
	SpellCardEffect spellCardEffect;

	void linkPlayerEnemy(); // pass player's location and power info to EnemyManager class
	void linkPlayerBoss(); // pass player's location and power info to Boss class
	void linkPlayerShotAndEnemy(); // pass player's shot info to EnemyManager class
	void linkPlayerShotAndBoss(); // pass player's shot info to Boss class
	void linkEnemyShotAndPlayer(); // pass Enemies' shots info to Player class
	void linkBossShotAndPlayer(); // pass Boss's shots info to Player class
	void linkPlayerBoard(); // pass player's health and power info to GameBoard class so that health and power can be shown

	// control Sound
	bool isSoundOn = false;
};