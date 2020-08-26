#include <DxLib.h>
#include "FPS.h"
#include "Round.h"

const static int LIST_LEN_MAX = 120; // max 120 frames
const static int FRAME_RATE = 60;
const static int UPINTVL = 60;
/*
   1 mili second = 1/1000 seconds => 1 second = 1000 mili seconds
   60fps => 1 frame takes 16.6666ms = 1000ms / 60fps
   
   in order to get 60fps
   at 1st frame => sleep for (int)(16.666ms * 1), total 16 ms
   at 2nd frame => sleep for (int)(16.666ms * 2), total 33 ms
   at 3rd frame => sleep for (int)(16.666ms * 3), total 49 ms
   ...
   at 60th frame => sleep for (int)(16.666ms * 60), total 999ms
   => in 1 second, 60 frams
*/

FPS::FPS() :
	_counter(0), _fps(0) 
{
}

void FPS::wait()
{
	_counter++;
	/* Sleep(int time)'s function is "don't proceed for 'time' mili seconds" */
	Sleep(getWaitTime());
	regist();
	if (_counter == UPINTVL) {
		updateAverage();
		_counter = 0;
	}
}

void FPS::draw() const
{
	if (_fps == 0) {
		return;
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%04.1ffps", _fps);
}

void FPS::regist()
{
	_list.push_back(GetNowCount()); // get the current time
	if (_list.size() > LIST_LEN_MAX) {
		_list.pop_front();
	}
}

unsigned FPS::getWaitTime() const
{
	int length = (int)_list.size();
	if (length == 0) {
		return 0;
	}

	int expectedTime = (int)(1000 / 60.f * (length)); // expected time
	int actuallyTookTime = GetNowCount() - _list.front(); // time that actually took to complete 1 frame
	int waitTime = expectedTime - actuallyTookTime;
	waitTime = waitTime > 0 ? waitTime : 0;
	return (unsigned)(waitTime);
}

void FPS::updateAverage()
{
	int length = (int)_list.size();
	if (length < LIST_LEN_MAX) {
		return;
	}
	int tookTime = _list.back() - _list.front();
	float average = (float)tookTime / (length - 1);
	if (average == 0) { // prevent the average being used to calculate something when 0
		return;
	}
	_fps = Round::roundPoint(1000 / average, 2);
}