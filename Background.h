#pragma once
#include "AbstractBackground.h"
#include <array>
#include <memory>

class Background final : public AbstractBackground
{
public:
	Background();
	~Background() = default;
	bool update() override;
	void draw() const override;

private:
	class backProp {
	public:
		const int img;
		float x, y;
		backProp(float x, float y, int img) : x(x), y(y), img(img) {}
	};
	const static int IMG_TOTAL = 2;
	std::array<std::shared_ptr<backProp>, IMG_TOTAL> _list;
};

