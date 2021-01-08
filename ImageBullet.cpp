#include "ImageBullet.h"
#include "Error.h"
#include <DxLib.h>

#define ERR(str) Error::finish(str, __FUNCTION__, __LINE__);

const float WEIGHT = 0.90f; // make the range a bit smaller than the actual radius of the bullet
const float ENLARGE = 1.6f; // the bullet images are enlarged when drawing them on the gameboard. Adjust range following the enlargement.

// hit range (mostly the middle white part of bullets)
// I have to change here as bullets are enlarged on the board
/*const float RANGE[] =
{
	4.5f * WEIGHT, // small ball
	10.0f * WEIGHT, // big ball
	4.5f * WEIGHT,// fuda
};

const int SORT_Z[] =
{
	2, // small ball
	3, // big ball
	1, // fuda
};*/

ImageBullet::ImageBullet()
{
	/* store size in vector*/
	_sizeList.push_back(new Size(18, 13)); // small ball
	_sizeList.push_back(new Size(29, 27)); // big ball
	_sizeList.push_back(new Size(9, 17)); // sharp bullet
	_sizeList.push_back(new Size(18, 20)); // fuda
	_sizeList.push_back(new Size(13, 62)); // Reimu's Bullet
	_sizeList.push_back(new Size(20, 17)); // Marisa's Bullet

	myLoadDivGraph("../img/shot_smallBall.png");
	myLoadDivGraph("../img/shot_bigBall.png");
	myLoadDivGraph("../img/shot_sharp.png");
	myLoadDivGraph("../img/shot_fuda.png");
	myLoadDivGraph("../img/ReimuBullet.png");
	myLoadDivGraph("../img/MarisaBullet.png");

	/* store range in vector*/
	_range.push_back(4.5f * WEIGHT * ENLARGE); // small ball
	_range.push_back(10.0f * WEIGHT * ENLARGE); // big ball
	_range.push_back(4.5f * WEIGHT * ENLARGE); // sharp bullet
	_range.push_back(4.5f * ENLARGE); // fuda
	_range.push_back(6.0f * ENLARGE); // Reimu's Bullet
	_range.push_back(10.0f * ENLARGE); // Marisa's Bullet
}

void ImageBullet::myLoadDivGraph(const char* fname)
{
	int id = _list.size(); // the size of the _list
	Size* size = _sizeList[id]; // the last index of _sizeList vector
	int* bullets = new int[eColorNum]; // *************** this never gets deleted??? ****************
	LoadDivGraph(fname, eColorNum, eColorNum, 1, size->getWidth(), size->getHeight(), bullets); // LoadDivGraph takes *handleArray to store imgs
	_list.push_back(bullets); // pushing an array to the _list array
}

/* returns the image of specified type and color */
int ImageBullet::getImage(unsigned int type, unsigned int color) const
{
	if (eTypeNum <= type) { // if the specified type doesn't exist in the "type" enum
		ERR("incorrect bullet type");
	}
	if (eColorNum <= color) { // if the specified color doesn't exist in the "color" enum
		ERR("incorrect bullet color")
	}
	return _list[type][color];
}

const Size* ImageBullet::getSize(unsigned int type) const
{
	if (_sizeList.size() <= type) {
		ERR("wrong index number");
	}
	return _sizeList[type];
}

float ImageBullet::getRange(int bulletType) const
{
	return _range[bulletType];
}