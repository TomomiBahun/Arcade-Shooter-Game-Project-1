#pragma once
#include "IOnSceneChangedListener.h"
#include "Parameter.h"

class IOnSceneChangedListener;

class AbstructScene
{
protected:
	IOnSceneChangedListener* _implSceneChanged;

public:
	AbstructScene(IOnSceneChangedListener* imply, const Parameter& parameter);
	virtual ~AbstructScene() = default;
	virtual void update() = 0;
	virtual void draw() const = 0;
};