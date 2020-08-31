#include "Image.h"
#include <DxLib.h>

Image::Image()
{
	_title = myLoadGraph("img/temp_title.png");
	_board = myLoadGraph("img/board.png");
	_back01 = myLoadGraph("img/back01.png");
	myLoadDivGraph("img/reimu.png", 6, 2, 3, 50, 50, _player);
	myLoadDivGraph("img/fire_blue.png", 4, 4, 1, 63, 50, _blueFire);
	myLoadDivGraph("img/fire_green.png", 4, 4, 1, 63, 50, _greenFire);
	_hitBox = myLoadGraph("img/hitBox.png");
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