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
	
	const int* getPlayer() const { return _player; }
	int const getGameBoard() { return _board; }
	int const getBack01() { return _back01; }
	const int* getBlueFire() const { return _blueFire; }
	const int* getGreenFire() const { return _greenFire; }

private:
	int myLoadGraph(const char*);
	int myLoadDivGraph(const char* fileName, int numTotalImg, int totalX, int totalY, int width, int height, int* buffer);

	std::vector<int> _images;
	int _player[6];
	int _board;
	int _back01;
	int _blueFire[4];
	int _greenFire[4];
};

