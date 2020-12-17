#pragma once
#include "AbstractScene.h"

class TitleMenu : public AbstructScene
{
public:
	TitleMenu(IOnSceneChangedListener* imply, const Parameter& parameter);
	virtual ~TitleMenu() = default;
	void update() override;
	void draw() const override;

private:
	bool isSoundOn = false;
};

