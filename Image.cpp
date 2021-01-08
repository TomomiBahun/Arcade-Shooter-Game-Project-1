#include "Image.h"
#include <DxLib.h>

Image::Image()
{
	/* image for Title and Option*/
	_title = myLoadGraph("../img/temp_title.png");
	_titleMenu = myLoadGraph("../img/titleMenu.png");
	_optionScene = myLoadGraph("../img/optionScene.png");
	_stageClear = myLoadGraph("../img/stageClear.png");
	_stage1 = myLoadGraph("../img/stage1.png");
	_stage1Title = myLoadGraph("../img/stageTitle.png");
	_gameStart = myLoadGraph("../img/GameStart.png");
	_extraStart = myLoadGraph("../img/ExtraStage.png");
	_practice = myLoadGraph("../img/Practice.png");
	_quit = myLoadGraph("../img/Quit.png");
	_selectFlower = myLoadGraph("../img/flowerSelect.png");
	_characterMenu = myLoadGraph("../img/characterMenu.png");
	_reimuLarge = myLoadGraph("../img/Reimu_Large.png");
	_marisaLarge = myLoadGraph("../img/Marisa_Large.png");
	_reimuDescription = myLoadGraph("../img/Reimu_Description.png");
	_marisaDescription = myLoadGraph("../img/Marisa_Description.png");

	/* images for game board*/
	_board = myLoadGraph("../img/board.png");
	_back01 = myLoadGraph("../img/back01.png");
	_backRan = myLoadGraph("../img/back_Ran.png");

	/* images player & Enemy icon*/
	//myLoadDivGraph("../img/reimu.png", 6, 2, 3, 50, 50, _player); //  old image of Reimu. Delete when game is complete
	myLoadDivGraph("../img/Reimudot.png", 15, 5, 3, 32, 49, _reimu);
	myLoadDivGraph("../img/Marisadot.png", 15, 5, 3, 32, 49, _marisa);
	myLoadDivGraph("../img/fire_blue.png", 4, 4, 1, 63, 50, _blueFire);
	myLoadDivGraph("../img/fire_green.png", 4, 4, 1, 63, 50, _greenFire);
	_yakumoRan = myLoadGraph("../img/YakumoRan.png");

	/* images player& Enemy normal pic*/
	_reimuNormal = myLoadGraph("../img/ReimuNormal.png");
	_reimuAngry = myLoadGraph("../img/ReimuAngry.png");
	_reimuSmile = myLoadGraph("../img/ReimuSmile.png");
	_reimuCreepy = myLoadGraph("../img/ReimuCreepy.png");
	_reimuConfused = myLoadGraph("../img/ReimuConfused.png");

	_ranNormal = myLoadGraph("../img/RanNormal.png");
	_ranTired = myLoadGraph("../img/RanTired.png");
	_ranCrying = myLoadGraph("../img/RanCrying.png");
	_ranConfident = myLoadGraph("../img/RanConfident.png");

	_marisaHappy = myLoadGraph("../img/MarisaHappy.png");
	_marisaSmile = myLoadGraph("../img/MarisaSmile.png");
	_marisaCreepy = myLoadGraph("../img/MarisaCreepy.png");

	/* Decorative images*/
	_hitBox = myLoadGraph("../img/hitBox.png");
	_healthText = myLoadGraph("../img/health_white.png");
	_powerText = myLoadGraph("../img/power_white.png");
	_health = myLoadGraph("../img/heart.png");
	myLoadDivGraph("../img/numbers.png", 10, 10, 1, 16, 18, _number);
	_messagebox = myLoadGraph("../img/messagebox.png");
	_bossHealth = myLoadGraph("../img/bossHealth.png");
	_spellCardLeft = myLoadGraph("../img/SpellCardLeft.png");
	_spellCardRight = myLoadGraph("../img/SpellCardRight.png");
	myLoadDivGraph("../img/circle.png", 4, 2, 2, 256, 256, _circle);
	_leaf = myLoadGraph("../img/leaf.png");
}

void Image::release()
{
	const int size = _images.size();
	for (int i = 0; i < size; i++) {
		DeleteGraph(_images[i]);
	}
	_images.clear();
}

int Image::myLoadGraph(const char* fileName)
{
	int ret = LoadGraph(fileName);
	_images.push_back(ret);
	return ret;
}

int Image::myLoadDivGraph(const char* fileName, int numTotalImg, int totalX, int totalY, int width, int height, int* buffer)
{
	int ret = LoadDivGraph(fileName, numTotalImg, totalX, totalY, width, height, buffer);
	for (int i = 0; i < numTotalImg; i++) {
		_images.push_back(buffer[i]);
	}
	return ret;
}