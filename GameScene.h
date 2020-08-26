#pragma once
#include "AbstractScene.h"
#include <memory>
#include "Player.h"
#include "GameBoard.h"
#include "AbstractBackground.h"
#include "EnemyManager.h"

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

private:
	//int _level;
	std::shared_ptr<Player> _player;
	std::shared_ptr<GameBoard> _board;
	std::shared_ptr<AbstractBackground> _background;
	std::shared_ptr<EnemyManager> _enemyManager;

	void linkPlayerEnemy();
	void linkPlayerShot();
	void linkEnemyShot();
};