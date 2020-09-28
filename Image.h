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
	int const getOptionScene() { return _optionScene; }

	/* images for game board*/
	int const getGameBoard() { return _board; }
	int const getBack01() { return _back01; }
	int const getBackRan() { return _backRan; }

	/* images player & Enemy icon*/
	const int* getPlayer() const { return _player; }
	const int* getBlueFire() const { return _blueFire; }
	const int* getGreenFire() const { return _greenFire; }
	int const getYakumoRan() { return _yakumoRan; }

	/* images player& Enemy normal pic*/
	int const getReimuNormal() { return _reimuNormal; }
	int const getReimuNormalLayered() { return _reimuNormalLayered; }
	int const getReimuAngry() { return _reimuAngry; }
	int const getReimuAngryLayered() { return _reimuAngryLayered; }

	int const getRanNormal() { return _ranNormal; }
	int const getRanNormalLayered() { return _ranNormalLayered; }
	int const getRanTired() { return _ranTired; }
	int const getRanTiredLayered() { return _ranTiredLayered; }
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

private:
	int myLoadGraph(const char*);
	int myLoadDivGraph(const char* fileName, int numTotalImg, int totalX, int totalY, int width, int height, int* buffer);

	std::vector<int> _images;
	/* image for Title and Option*/
	int _title;
	int _optionScene;

	/* images for game board*/
	int _board;
	int _back01;
	int _backRan;

	/* images player & Enemy icon*/
	int _player[6];
	int _blueFire[4];
	int _greenFire[4];
	int _yakumoRan;

	/* images player& Enemy normal pic*/
	int _reimuNormal;
	int _reimuNormalLayered;
	int _reimuAngry;
	int _reimuAngryLayered;
	int _ranNormal;
	int _ranNormalLayered;
	int _ranTired;
	int _ranTiredLayered;
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
};

