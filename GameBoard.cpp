#include "GameBoard.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"

bool GameBoard::update()
{
	return true;
}

void GameBoard::draw() const
{
	DrawGraph(1, 0, Image::getIns()->getGameBoard(), TRUE);
}