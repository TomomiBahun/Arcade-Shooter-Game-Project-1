#pragma once
#include "AbstractScene.h"

class CharacterMenu : public AbstructScene
{
public:
	CharacterMenu(IOnSceneChangedListener* imply, const Parameter& parameter);
	virtual ~CharacterMenu() = default;
	void update() override;
	void draw() const override;

private:
	int _choiceAt;
	int _counter;
};