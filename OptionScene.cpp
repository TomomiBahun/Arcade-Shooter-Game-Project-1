#include "OptionScene.h"
#include <DxLib.h>
#include "Define.h"
#include "GameScene.h"
#include "keyboard.h"
#include "Image.h"

OptionScene::OptionScene(IOnSceneChangedListener* imply, const Parameter& parameter) : AbstructScene(imply, parameter)
{
	character = parameter.get(GameScene::ParameterTagCharacter);
}

/* always update() => draw() */
void OptionScene::update()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_B) == 1) {

		Parameter parameter; // no need to specify the parameter
		const bool stackClear = true;

		_implSceneChanged->onSceneChanged(eScene::Menu, parameter, stackClear);
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {

		Parameter parameter; // no need to specify the parameter
		parameter.set(GameScene::ParameterTagCharacter, character);
		const bool stackClear = false;

		// pop the OptionScene from the stack, and play the same game
		_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
	}
}

/* always update() => draw()*/
void OptionScene::draw() const
{
	DrawGraph(1, 0, Image::getIns()->getOptionScene(), TRUE);
}