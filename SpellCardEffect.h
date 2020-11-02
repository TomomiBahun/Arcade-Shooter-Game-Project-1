#pragma once
#include "Task.h"
#include <array>
#include <memory>

class SpellCardEffect : public Task
{
public:
	SpellCardEffect();
	virtual ~SpellCardEffect() = default;
	bool update() override;
	void draw() const override;
	bool getEffectStatus() { return _isEffectOn; }

private:
	class backProp {
	public:
		const int img;
		float x, y;
		backProp(float x, float y, int img) : x(x), y(y), img(img) {}
	};
	const static int IMG_TOTAL = 2;
	int _counter;
	int _brightnessLetter;
	int _brightnessBoss;
	int _y;
	bool _isEffectOn;
	std::array<std::shared_ptr<backProp>, IMG_TOTAL> _spellCardLeft;
	std::array<std::shared_ptr<backProp>, IMG_TOTAL> _spellCardRight;

	void init();
};

