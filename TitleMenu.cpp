#include "TitleMenu.h"
#include "keyboard.h"
#include <DxLib.h>


TitleMenu::TitleMenu(IOnSceneChangedListener* imply, const Parameter& parameter) : AbstructScene(imply, parameter)
{
	// do nothing with the parameter
}

/* always update() => draw() */
void TitleMenu::update()
{
	/*if (Keyboard::getIns()->getPressingCount(KEY_INPUT_E) == 1) {
		// set the parameter (which level is it? should the stack be cleared?)
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::eLevel::easy);
		const bool stackClear = false;

		// use the parameter that we set above to specify next scene
		_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
	}*/
	if (!isSoundOn) {
		PlaySoundMem(Sound::getIns()->getTitleSound(), DX_PLAYTYPE_LOOP);
		isSoundOn = true;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {
		// set the parameter (which level is it? should the stack be cleared?)
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::eLevel::normal);
		const bool stackClear = false;

		// use the parameter that we set above to specify next scene
		_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
		StopSoundMem(Sound::getIns()->getTitleSound());
	}
}

/* always update() => draw()*/
void TitleMenu::draw() const
{
	//DrawString(100, 100, "Title", GetColor(255, 0, 0));
	DrawGraph(1, 0, Image::getIns()->getTitle(), TRUE);
}