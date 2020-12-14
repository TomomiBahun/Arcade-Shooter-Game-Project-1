#pragma once
#include "AbstractScene.h"

class TitleScene : public AbstructScene
{
public:
	TitleScene(IOnSceneChangedListener* imply, const Parameter& parameter);
	virtual ~TitleScene() = default;
	void update() override;
	void draw() const override;

private:
	bool isSoundOn = false;
};