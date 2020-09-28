#pragma once
#include "Singleton.h"
#include <vector>

class Size {
public:
	Size() : w(0), h(0) {}
	Size(int w, int h) : w(w), h(h) {}
	int getWidth() const { return w; }
	int getHeight() const { return h; }

private:
	int w, h;
};

class ImageBullet final : public Singleton<ImageBullet>
{
public:
	enum eBulletType {
		smallBall,
		bigBall,
		sharpBullet,
		fuda,
		reimuBullet,
		eTypeNum
	};

	enum eBulletColor {
		eRed, // 0
		eOrange, // 1
		eYellow, // 2
		eGreen, // 3
		eAqua, // 4
		eBlue, // 5
		ePurple, // 6
		eGray, // 7
		eColorNum,
	};
	
	//const static float RANGE[];
	//const static float SORT_Z[];
	ImageBullet();
	virtual ~ImageBullet() = default;
	int getImage(unsigned int type, unsigned int color) const; // get a bullet by specifying both type and color parameters
	const Size* getSize(unsigned int type) const;
	float getRange(int bulletType) const;
	


private:
	std::vector<int*> _list; // list is an array of arrays (each type have 8 colors)
	std::vector<Size*> _sizeList;
	std::vector<float> _range;
	std::vector<float> _sort;

	void load() {}
	void myLoadDivGraph(const char* fname);
};

