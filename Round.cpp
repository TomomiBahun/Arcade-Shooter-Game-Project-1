#include "Round.h"
#include <cmath>
#include <DxLib.h>

float Round::roundPoint(float val, int point) {
	float ret;
	ret = val * pow(10.f, + point - 1);
	ret = (float)(int)(ret + 0.5f);
	return ret * pow(10.f, -point + 1);
}