#include "CharacterMenu.h"
#include "Keyboard.h"
#include "Image.h"
#include "Sound.h"
#include "Define.h"
#include "GameScene.h" // It might not needed
#include <DxLib.h>

const static int CHOICE_MIN = 0;
const static int CHOICE_MAX = 1;
const static int BRIGHTNESS_MIN = 110;
const static int BRIGHTNESS_MAX = 255;

CharacterMenu::CharacterMenu(IOnSceneChangedListener* imply, const Parameter& parameter) : AbstructScene(imply, parameter)
{
	_choiceAt = 0; // default 0 -> Reimu
	_counter = 0; // counter is used for drawing character images
}

void CharacterMenu::update()
{
	// play music if it's not on yet
	if (!CheckSoundMem(Sound::getIns()->getTitleSound())) {
		PlaySoundMem(Sound::getIns()->getTitleSound(), DX_PLAYTYPE_LOOP);
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1) {
		_choiceAt++;
		_counter = 0; // reset the counter
		if (_choiceAt > CHOICE_MAX) {
			_choiceAt = CHOICE_MAX;
		}
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1) {
		_choiceAt--;
		_counter = 0; // reset the counter
		if (_choiceAt < CHOICE_MIN) {
			_choiceAt = CHOICE_MIN;
		}
	}

	// go to the game screen when player choose a character
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_NUMPADENTER) == 1) {
		StopSoundMem(Sound::getIns()->getTitleSound());

		// set the parameter (which character? should the stack be cleared?)
		Parameter parameter;
		if (_choiceAt == 0) {
			parameter.set(GameScene::ParameterTagCharacter, Define::eCharacter::reimu);
		}
		else {
			parameter.set(GameScene::ParameterTagCharacter, Define::eCharacter::marisa);
		}
		const bool stackClear = false; // the next scene will be added to the stack

		// use the parameter that we set above to specify next scene
		_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
	}

	// go back to the title menu when 'Q' is pressed
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Q) == 1) {
		Parameter parameter;
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Back, parameter, stackClear);
	}

	_counter++;
}

void CharacterMenu::draw() const
{

	// Draw character menu background
	DrawGraph(1, 0, Image::getIns()->getCharacterMenu(), TRUE);

	// if the curser is at Reimu
	if (_choiceAt == 0) {
		SetDrawBright(BRIGHTNESS_MIN, BRIGHTNESS_MIN, BRIGHTNESS_MIN);
			DrawRotaGraphF(Define::CENTER_X + 150, Define::CENTER_Y + 100, 0.6, 0, Image::getIns()->getMarisaLarge(), TRUE);
		SetDrawBright(BRIGHTNESS_MAX, BRIGHTNESS_MAX, BRIGHTNESS_MAX);
			DrawRotaGraphF(Define::CENTER_X - 100, Define::CENTER_Y + 100, 0.6, 0, Image::getIns()->getReimuLarge(), TRUE);
			DrawRotaGraphF(Define::CENTER_X + 550, Define::CENTER_Y + 100, 0.35, 0, Image::getIns()->getReimuDescription(), TRUE);
	}
	else { // if the curser is at Marisa
		SetDrawBright(BRIGHTNESS_MIN, BRIGHTNESS_MIN, BRIGHTNESS_MIN);
			DrawRotaGraphF(Define::CENTER_X - 100, Define::CENTER_Y + 100, 0.6, 0, Image::getIns()->getReimuLarge(), TRUE);
		SetDrawBright(BRIGHTNESS_MAX, BRIGHTNESS_MAX, BRIGHTNESS_MAX);
			DrawRotaGraphF(Define::CENTER_X + 150, Define::CENTER_Y + 100, 0.6, 0, Image::getIns()->getMarisaLarge(), TRUE);
			DrawRotaGraphF(Define::CENTER_X + 550, Define::CENTER_Y + 100, 0.35, 0, Image::getIns()->getMarisaDescription(), TRUE);
	}
}