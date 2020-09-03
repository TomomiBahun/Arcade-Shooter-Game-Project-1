#include "AbstractScene.h"

/*constructor
@param imply listener to change scenes
@param parameter parameter which will be passed by previous scene */
AbstructScene::AbstructScene(IOnSceneChangedListener* imply, const Parameter& parameter) :
	_implSceneChanged(imply)
{
}