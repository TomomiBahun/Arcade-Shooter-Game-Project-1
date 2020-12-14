#include "SpellCardEffect.h"
#include "Image.h"
#include "Define.h"
#include "Sound.h"
#include <DxLib.h>

using namespace std;

const static int IMG_WIDTH = 896;
const static float SCROLL_SPEED = 4.5f;
const static int MAX_BRIGHTNESS = 255;

SpellCardEffect::SpellCardEffect() : 
	_counter(0),
	_brightnessLetter(0), _brightnessBoss(0),
	_y(Define::CENTER_Y + 100),
	_isEffectOn(true)
{
	_spellCardLeft[0] = make_shared<backProp>(IMG_WIDTH * 0, Define::IN_Y, Image::getIns()->getSpellCardLeft());
	_spellCardLeft[1] = make_shared<backProp>(IMG_WIDTH * 1, Define::IN_Y, Image::getIns()->getSpellCardLeft());
	_spellCardRight[0] = make_shared<backProp>(IMG_WIDTH * 0, Define::IN_Y, Image::getIns()->getSpellCardRight());
	_spellCardRight[1] = make_shared<backProp>(IMG_WIDTH * 1, Define::IN_Y, Image::getIns()->getSpellCardRight());
}

bool SpellCardEffect::update()
{
	_counter++;

	/* move SpellCard letter effect */
	if (_spellCardLeft.size() > 1) {
		for (int i = 0; i < IMG_TOTAL; i++) {
			_spellCardLeft[i]->x -= SCROLL_SPEED;
			if (_spellCardLeft[i]->x < -IMG_WIDTH) { // when the whole image scrolls the area
				_spellCardLeft[i]->x += IMG_WIDTH * 2; // put the img below the game board
			}
		}
	}
	if (_spellCardRight.size() > 1) {
		for (int i = 0; i < IMG_TOTAL; i++) {
			_spellCardRight[i]->x += SCROLL_SPEED;
			if (_spellCardRight[i]->x > IMG_WIDTH) { // when the whole image scrolls the area
				_spellCardRight[i]->x -= IMG_WIDTH * 2; // put the img below the game board
			}
		}
	}

	/* control transparency of SpellCard letter effect ... 140 frames total*/
	if (_counter < 100) {
		_brightnessLetter += 5;
		if (_brightnessLetter > 200) {
			_brightnessLetter = 200;
		}
	}
	else {
		_brightnessLetter -= 5;
		if (_brightnessLetter < 0) {
			_brightnessLetter = 0;
		}
	}

	/* control transparency and location of Boss image*/
	if (_counter < 100) {
		_brightnessBoss += 5;
		if (_brightnessBoss > 200) {
			_brightnessBoss = 200;
		}
		_y -= 5;
	}
	else {
		_brightnessBoss -= 10;
		if (_brightnessBoss < 0) {
			_brightnessBoss = 0;
		}
		else {
			_y -= 5;
		}
	}

	/* control the location of Boss image */
	if (_counter > 121 ) {
		_isEffectOn = false;
		init();
		return false;
	}
	else {
		_isEffectOn = true;
	}

	if (!CheckSoundMem(Sound::getIns()->getSpellCardEffectSound())) {
		PlaySoundMem(Sound::getIns()->getSpellCardEffectSound(), DX_PLAYTYPE_BACK);
	}

	return true;
}

void SpellCardEffect::draw() const
{
	// draw within just the movable area
	SetDrawArea(0, 0, Define::OUTER_W, Define::OUTER_H);

	/* draw SpellCard letter Effect*/
	if (_spellCardLeft.size() > 1 && _spellCardRight.size() > 1) {
		for (int i = 0; i < IMG_TOTAL; i++) {
			if (_brightnessLetter != 0) {
				/* use specific brightness to draw letters*/
				SetDrawBright(_brightnessLetter, _brightnessLetter, _brightnessLetter);
				DrawGraphF(_spellCardLeft[i]->x, _spellCardLeft[i]->y, _spellCardLeft[i]->img, TRUE);
				DrawGraphF(_spellCardRight[i]->x, _spellCardRight[i]->y, _spellCardRight[i]->img, TRUE);
			}
		}
	}
	
	/* use specific brightness to draw boss image. Boss image moves*/
	SetDrawBright(_brightnessBoss, _brightnessBoss, _brightnessBoss);
	if (_brightnessBoss != 0) {
		DrawRotaGraphF(Define::CENTER_X+100, _y, 1.50, 0.0, Image::getIns()->getYakumoRan(), TRUE);
	}

	/* set the brightness back to normal*/
	SetDrawBright(MAX_BRIGHTNESS, MAX_BRIGHTNESS, MAX_BRIGHTNESS);
	SetDrawArea(0, 0, Define::WIN_W, Define::WIN_H);
}

void SpellCardEffect::init()
{
	_counter = 0;
	_brightnessLetter = 0;
	_brightnessBoss = 0;
	_y = Define::CENTER_Y + 100;
	StopSoundMem(Sound::getIns()->getSpellCardEffectSound());
}