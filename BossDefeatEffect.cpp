#include "BossDefeatEffect.h"
#include "Define.h"
#include "Sound.h"

const static int MAX_BRIGHTNESS = 255;

BossDefeatEffect::BossDefeatEffect() : 
	_flashCount(0), _flashCountMax(40), _flashBrightness(0), _flashFlag(false)
{

}

bool BossDefeatEffect::update() {
	_flashFlag = true;

	// update for the flash Effect
	if (_flashCount < _flashCountMax) {
		_flashBrightness += 255.0 / _flashCountMax;
		if (_flashCount == 0) {
			PlaySoundMem(Sound::getIns()->getBossDefeatSound(), DX_PLAYTYPE_BACK);
		}
	}
	else {
		_flashBrightness -= 255.0 / _flashCountMax;
		if (_flashBrightness < 0) {
			_flashFlag = false;
		}
	}

	if (_flashFlag == false) {
		return false;
	}

	// update for the leaf Effect
	if (_flashCount == 0) { // set up the leaf images at the same time as the start of the flash effect
		for (int i = 0; i < 32; i++) {
			setLeaves(_bossX, _bossY, 6.0, Define::PI + (Define::PI / 16 * i));
		}
	}
	else { // keep updating leaves (move leaves)
		updateLeaves();
	}

	_flashCount++;
	_leafBrightness += 4;
	return true;
}

void BossDefeatEffect::draw() const {
	// draw flash effect
	/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(_flashBrightness));
	DrawBox(Define::IN_X, Define::IN_Y, Define::OUTER_W, Define::OUTER_H, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/

	// draw leaves
	for (int i = 0; i < leaves.size(); i++) {
		leaves.at(i).draw();
	}

	// draw flash effect
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(_flashBrightness));
	DrawBox(Define::IN_X, Define::IN_Y, Define::OUTER_W, Define::OUTER_H, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void BossDefeatEffect::setLeaves(float x, float y, float speed, float angle) {
	// set leaves
	leaf tempLeaf = leaf(x, y, speed, angle);
	tempLeaf.setEnlargeRate(2.0 + (GetRand(30)/10));
	tempLeaf.setRamdomNum(GetRand(5));
	leaves.push_back(tempLeaf);
}

void BossDefeatEffect::updateLeaves() {
	for (int i = 0; i < leaves.size(); i++) {
		// slow down and rotate the leaves
		if (leaves.at(i).getRandom() > 2) {
			leaves.at(i).setAngle(leaves.at(i).getAngle() + Define::PI / 360);
			leaves.at(i).setSpeed(leaves.at(i).getSpeed() - 0.01);
		}
		else {
			leaves.at(i).setAngle(leaves.at(i).getAngle() - Define::PI / 360);
			leaves.at(i).setSpeed(leaves.at(i).getSpeed() - 0.02);
		}
		// keep moving the leaves images
		float px = leaves.at(i).getX() + cos(leaves.at(i).getAngle()) * leaves.at(i).getSpeed();
		float py = leaves.at(i).getY() + sin(leaves.at(i).getAngle()) * leaves.at(i).getSpeed();
		leaves.at(i).setX(px);
		leaves.at(i).setY(py);
	}
}