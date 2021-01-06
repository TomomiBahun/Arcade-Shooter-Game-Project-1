#pragma once
#include "Singleton.h"
#include <vector>

class Image final : public Singleton<Image>
{
public:
	Image();
	~Image() = default;
	void load() {}
	void release();

	/* image for Title and Option*/
	int const getTitle() { return _title; }
	int const getTitleMenu() { return _titleMenu; }
	int const getOptionScene() { return _optionScene; }
	int const getStageClear() { return _stageClear; }
	int const getStage1() { return _stage1; }
	int const getStage1Title() { return _stage1Title; }
	int const getGameStart() { return _gameStart; }
	int const getExtraStart() { return _extraStart; }
	int const getPractice() { return _practice; }
	int const getQuit() { return _quit; }
	int const getSelectFlower() { return _selectFlower; }
	int const getCharacterMenu() { return _characterMenu; }
	int const getReimuLarge() { return _reimuLarge; }
	int const getMarisaLarge() { return _marisaLarge; }
	int const getReimuDescription() { return _reimuDescription; }
	int const getMarisaDescription() { return _marisaDescription; }

	/* images for game board*/
	int const getGameBoard() { return _board; }
	int const getBack01() { return _back01; }
	int const getBackRan() { return _backRan; }

	/* images player & Enemy icon*/
	// const int* getPlayer() const { return _player; } old image of Reimu. Delete when game is complete
	const int* getReimu() const { return _reimu; }
	const int* getBlueFire() const { return _blueFire; }
	const int* getGreenFire() const { return _greenFire; }
	int const getYakumoRan() { return _yakumoRan; }

	/* images player& Enemy normal pic*/
	int const getReimuNormal() { return _reimuNormal; }
	int const getReimuNormalLayered() { return _reimuNormalLayered; }
	int const getReimuAngry() { return _reimuAngry; }
	int const getReimuAngryLayered() { return _reimuAngryLayered; }
	int const getReimuSmile() { return _reimuSmile; }
	int const getReimuSmileLayered() { return _reimuSmileLayered; }
	int const getReimuCreepy() { return _reimuCreepy; }
	int const getReimuCreepyLayered() { return _reimuCreepyLayered; }
	int const getReimuConfused() { return _reimuConfused; }

	int const getRanNormal() { return _ranNormal; }
	int const getRanNormalLayered() { return _ranNormalLayered; }
	int const getRanTired() { return _ranTired; }
	int const getRanTiredLayered() { return _ranTiredLayered; }
	int const getRanCrying() { return _ranCrying; }
	int const getRanCryingLayered() { return _ranCryingLayered; }
	int const getRanConfident() { return _ranConfident; }

	/* Decorative images*/
	int const getHitBox(){ return _hitBox; }
	int const getHealthText() { return _healthText; }
	int const getPowerText() { return _powerText; }
	int const getHealth() { return _health; }
	const int* getNumber() { return _number; }
	int const getMessagebox() { return _messagebox; }
	int const getBossHealth() { return _bossHealth; }
	int const getSpellCardLeft() { return _spellCardLeft; }
	int const getSpellCardRight() { return _spellCardRight; }
	const int* getCircle() { return _circle; }
	int const getLeaf() { return _leaf; }

private:
	int myLoadGraph(const char*);
	int myLoadDivGraph(const char* fileName, int numTotalImg, int totalX, int totalY, int width, int height, int* buffer);

	std::vector<int> _images;
	/* image for Title and Option*/
	int _title;
	int _titleMenu;
	int _optionScene;
	int _stageClear;
	int _stage1;
	int _stage1Title;
	int _gameStart;
	int _extraStart;
	int _practice;
	int _quit;
	int _selectFlower;
	int _characterMenu;
	int _reimuLarge;
	int _marisaLarge;
	int _reimuDescription;
	int _marisaDescription;

	/* images for game board*/
	int _board;
	int _back01;
	int _backRan;

	/* images player & Enemy icon*/
	//int _player[6]; // old image of Reimu. Delete when game is complete
	int _reimu[15];
	int _blueFire[4];
	int _greenFire[4];
	int _yakumoRan;

	/* images player& Enemy normal pic*/
	int _reimuNormal;
	int _reimuNormalLayered;
	int _reimuAngry;
	int _reimuAngryLayered;
	int _reimuSmile;
	int _reimuSmileLayered;
	int _reimuCreepy;
	int _reimuCreepyLayered;
	int _reimuConfused;
	int _ranNormal;
	int _ranNormalLayered;
	int _ranTired;
	int _ranTiredLayered;
	int _ranCrying;
	int _ranCryingLayered;
	int _ranConfident;

	/* Decorative images*/
	int _hitBox;
	int _healthText;
	int _powerText;
	int _health;
	int _number[10];
	int _messagebox;
	int _bossHealth;
	int _spellCardLeft;
	int _spellCardRight;
	int _circle[4];
	int _leaf;
};

