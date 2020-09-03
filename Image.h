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

	int const getTitle() { return _title; }
	int const getOptionScene() { return _optionScene; }
	int const getGameBoard() { return _board; }
	int const getBack01() { return _back01; }
	int const getBackRan() { return _backRan; }
	const int* getPlayer() const { return _player; }
	const int* getBlueFire() const { return _blueFire; }
	const int* getGreenFire() const { return _greenFire; }
	int const getYakumoRan() { return _yakumoRan; }
	int const getHitBox(){ return _hitBox; }
	int const getHealthText() { return _healthText; }
	int const getPowerText() { return _powerText; }
	int const getHealth() { return _health; }
	const int* getNumber() { return _number; }

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

	/* images player & Enemy*/
	int _player[6];
	int _blueFire[4];
	int _greenFire[4];
	int _yakumoRan;

	/* Decorative images*/
	int _hitBox;
	int _healthText;
	int _powerText;
	int _health;
	int _number[10];
};

