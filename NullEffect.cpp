#include "NullEffect.h"

bool NullEffect::update()
{
	_counter++;
	if (_counter < 10) {
		_isEffectOn = true;
	}
	else {
		_isEffectOn = false;
	}

	return true;
}

void NullEffect::draw() const
{
}