#pragma once

#include "Singleton.h"
#include <array>

class Keyboard final : public Singleton<Keyboard>
{
	Keyboard() = default;
	friend Singleton<Keyboard>;

public:
	bool update();
	int getPressingCount(int keyCode); // get the num of frames
	int getReleasingCount(int keyCode); // get hte num of frames

private:
	static const int KEY_NUM = 256; // total num of keys on a keyboard
	std::array<int, KEY_NUM> _pressingCount;
	std::array<int, KEY_NUM> _releasingCount;

	bool isCodeAvailable(int keycode); // check is the keycode is available
};
