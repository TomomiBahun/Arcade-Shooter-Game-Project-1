#pragma once

#include <list>

class FPS
{
public:
	FPS();
	void wait();
	void draw() const;

private:
	std::list<int> _list;
	float _fps;
	unsigned _counter;

	void updateAverage();
	void regist();
	unsigned getWaitTime() const;
};

