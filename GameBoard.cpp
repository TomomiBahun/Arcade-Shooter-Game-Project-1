#include "GameBoard.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"
#include "Player.h"

bool GameBoard::update()
{
	return true;
}

void GameBoard::draw() const
{
	DrawGraph(1, 0, Image::getIns()->getGameBoard(), TRUE);
	DrawRotaGraph(Define::INNER_W + 250, Define::CENTER_Y - 250, 1.6, 0.0, Image::getIns()->getHealthText(), TRUE);
	//DrawRotaGraph(Define::INNER_W + 250, Define::CENTER_Y - 100, 1.6, 0.0, Image::getIns()->getPowerText(), TRUE);
	
	/* drawing health icons*/
	if (_playerHealth == 0) {
		return;
	}
	for (int i = 0; i < _playerHealth/10; i++) {
		DrawRotaGraph(Define::INNER_W + 160 + i*40, Define::CENTER_Y - 200, 1.6, 0.0, Image::getIns()->getHealth(), TRUE);
	}
}

void GameBoard::setPlayerProperty(int health, int power)
{
	_playerHealth = health;
	_playerPower = power;
}