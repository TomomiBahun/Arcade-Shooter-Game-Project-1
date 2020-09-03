#include "OptionScene.h"
#include <DxLib.h>
#include "Define.h"
#include "GameScene.h"
#include "keyboard.h"
#include "Image.h"

OptionScene::OptionScene(IOnSceneChangedListener* imply, const Parameter& parameter) : AbstructScene(imply, parameter)
{
	// do nothing with the parameter
}

/* always update() => draw() */
void OptionScene::update()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_B) == 1) {
		// set the parameter (which level is it? should the stack be cleared?)
		Parameter parameter;
		const bool stackClear = true;
		// use the parameter that we set above to specify next scene
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {
		// set the parameter (which level is it? should the stack be cleared?)
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::eLevel::normal);
		const bool stackClear = false;

		// use the parameter that we set above to specify next scene
		_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
	}
}

/* always update() => draw()*/
void OptionScene::draw() const
{
	//DrawString(100, 100, "Title", GetColor(255, 0, 0));
	DrawGraph(1, 0, Image::getIns()->getOptionScene(), TRUE);
}