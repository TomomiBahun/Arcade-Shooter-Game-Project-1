#pragma once
#include "AbstractScene.h"

class OptionScene : public AbstructScene
{
public:
	OptionScene(IOnSceneChangedListener* imply, const Parameter& parameter);
	virtual ~OptionScene() = default;
	void update() override;
	void draw() const override;
};