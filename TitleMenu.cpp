#include "TitleMenu.h"
#include <DxLib.h>
#include "Define.h"
#include "GameScene.h"
#include "keyboard.h"
#include "Image.h"
#include "Sound.h"

const static int CHOICE_MAX = 1;
const static int CHOICE_MIN = 0;

TitleMenu::TitleMenu(IOnSceneChangedListener* imply, const Parameter& parameter) : AbstructScene(imply, parameter)
{
	choiceAt = 0;
	flowerCounter = 0;
	choices.insert({ CHOICE_MIN, eScene::CharacterSelect }); // 0 ----->> should be charactor select screen
	//choices.insert({ 1, eScene::Extra }); // 1
	//choices.insert({ 2, eScene::practice }); // 2
	choices.insert({ CHOICE_MAX, eScene::Quit }); // 3
}

/* always update() => draw() */
void TitleMenu::update()
{
	// play music if it's not on yet (it should be on)
	// next scene will need the same music, so no command to stop the music in this class
	if (!CheckSoundMem(Sound::getIns()->getTitleSound())) {
		PlaySoundMem(Sound::getIns()->getTitleSound(), DX_PLAYTYPE_LOOP);
	}

	// when the player hits enter, call the specified menu
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_NUMPADENTER) == 1) {
		PlaySoundMem(Sound::getIns()->getProceed(), DX_PLAYTYPE_BACK);

		// set the parameter (which level is it? should the stack be cleared?)
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::eLevel::normal);
		const bool stackClear = false; // the next scene will be added to the stack

		// use the parameter that we set above to specify next scene
		_implSceneChanged->onSceneChanged(choices.at(choiceAt), parameter, stackClear);
	}

	// when the user use up/down key at the menu
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {
		choiceAt++; // move down the curser
		flowerCounter = 0; // initialize the flower counter

		// if the curser is at the bottom, move it back to the top
		if (choiceAt > CHOICE_MAX) {
			choiceAt = CHOICE_MIN;
		}
	}
	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {
		choiceAt--;
		flowerCounter = 0; //initialize the flower counter
		if (choiceAt < CHOICE_MIN) {
			choiceAt = CHOICE_MAX;
		}
	}

	flowerCounter++; // flower counter shoud keep going. When the curser moves up/down, it gets initialized.
	if (flowerCounter > 30) {
		flowerCounter = 30; // max for flower Counter
	}
}

/* always update() => draw()*/
void TitleMenu::draw() const
{
	// draw the title menu
	DrawGraph(1, 0, Image::getIns()->getTitleMenu(), TRUE);

	// always draw the menu in dark
	SetDrawBright(150, 150, 150);
		DrawGraph(Define::CENTER_X + 300, Define::CENTER_Y + 20, Image::getIns()->getGameStart(), TRUE);
		DrawGraph(Define::CENTER_X + 300, Define::CENTER_Y + 100, Image::getIns()->getExtraStart(), TRUE);
		DrawGraph(Define::CENTER_X + 300, Define::CENTER_Y + 180, Image::getIns()->getPractice(), TRUE);
		DrawGraph(Define::CENTER_X + 200, Define::CENTER_Y + 260, Image::getIns()->getQuit(), TRUE);
	SetDrawBright(255, 255, 255);

	// move the curser following the up/down key
	/**** Currently Skipping "Extra Stage" and "Practice" ****/
	switch (choiceAt) {
	case 0:
		DrawRotaGraphF(Define::CENTER_X + 600 + flowerCounter, Define::CENTER_Y + 75, 0.5, 0.0, Image::getIns()->getSelectFlower(), TRUE);
		DrawGraph(Define::CENTER_X + 300, Define::CENTER_Y + 20, Image::getIns()->getGameStart(), TRUE);
		break;
	case 1:
		DrawRotaGraphF(Define::CENTER_X + 450 + flowerCounter, Define::CENTER_Y + 315, 0.5, 0.0, Image::getIns()->getSelectFlower(), TRUE);
		DrawGraph(Define::CENTER_X + 200, Define::CENTER_Y + 260, Image::getIns()->getQuit(), TRUE);
		break;
	/*case 1:
		DrawRotaGraphF(Define::CENTER_X + 550 + flowerCounter, Define::CENTER_Y + 155, 0.5, 0.0, Image::getIns()->getSelectFlower(), TRUE);
		DrawGraph(Define::CENTER_X + 300, Define::CENTER_Y + 100, Image::getIns()->getExtraStart(), TRUE);
		break;
	case 2:
		DrawRotaGraphF(Define::CENTER_X + 600 + flowerCounter, Define::CENTER_Y + 235, 0.5, 0.0, Image::getIns()->getSelectFlower(), TRUE);
		DrawGraph(Define::CENTER_X + 300, Define::CENTER_Y + 180, Image::getIns()->getPractice(), TRUE);
		break;
	case 3:
		DrawRotaGraphF(Define::CENTER_X + 450 + flowerCounter, Define::CENTER_Y + 315, 0.5, 0.0, Image::getIns()->getSelectFlower(), TRUE);
		DrawGraph(Define::CENTER_X + 200, Define::CENTER_Y + 260, Image::getIns()->getQuit(), TRUE);
		break;*/
	default:
		break;
	}
}