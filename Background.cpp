#include "Background.h"
#include "Image.h"
#include "Define.h"
#include <DxLib.h>

using namespace std;

const static int IMG_HEIGHT = 879;
const static float SCROLL_SPEED = 2.0f;

Background::Background()
{
	_list[0] = make_shared<backProp>(0, IMG_HEIGHT * 0, Image::getIns()->getBack01());
	_list[1] = make_shared<backProp>(0, IMG_HEIGHT * 1, Image::getIns()->getBack01());
}

bool Background::update()
{
	for (int i = 0; i < IMG_TOTAL; i++) {
		_list[i]->y -= SCROLL_SPEED;
		if (_list[i]->y < -IMG_HEIGHT) { // when the whole image scrolls the area
			_list[i]->y += IMG_HEIGHT * 2; // put the img below the game board
		}
	}
	return true;
}

void Background::draw() const
{
	SetDrawArea(0, 0, Define::OUTER_W, Define::OUTER_H); // just the movable area
	for (int i = 0; i < IMG_TOTAL; i++) {
		DrawGraphF(_list[i]->x, _list[i]->y, _list[i]->img, FALSE);
	}
	SetDrawArea(0, 0, Define::WIN_W, Define::WIN_H);
}