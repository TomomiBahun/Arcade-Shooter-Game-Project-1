#include "TitleScene.h"
#include <DxLib.h>
#include "Define.h"
#include "GameScene.h"
#include "keyboard.h"
#include "Image.h"
#include "Sound.h"

TitleScene::TitleScene(IOnSceneChangedListener* imply, const Parameter& parameter) : AbstructScene(imply, parameter)
{
	// do nothing with the parameter
}

/* always update() => draw() */
void TitleScene::update()
{
	if (!isSoundOn) {
		PlaySoundMem(Sound::getIns()->getTitleSound(), DX_PLAYTYPE_LOOP);
		isSoundOn = true;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {

		Parameter parameter; // no need to specify the parameter here
		const bool stackClear = true; // player won't come back to this screen

		// use the parameter that we set above to specify next scene
		_implSceneChanged->onSceneChanged(eScene::Menu, parameter, stackClear);
	}
}

/* always update() => draw()*/
void TitleScene::draw() const
{
	DrawGraph(1, 0, Image::getIns()->getTitle(), TRUE);
}