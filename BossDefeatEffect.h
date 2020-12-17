#pragma once
#include "Task.h"
#include "Image.h"
#include <vector>
#include <DxLib.h>
class BossDefeatEffect : public Task
{
public:
	BossDefeatEffect();
	~BossDefeatEffect() = default;
	bool update() override;
	void draw() const override;
	bool getFlashFlag() const { return _flashFlag; }
	int getFlashCount() const { return _flashCount; }
	int getFlashBrightness() const { return _flashBrightness; }
	void setBossX(float x) { _bossX = x; }
	void setBossY(float y) { _bossY = y; }

private:
	int _flashCount;
	int _flashCountMax;
	int _flashBrightness;
	bool _flashFlag;
	float _bossX, _bossY;
	int _leafBrightness;

	// internal class to hold leaves
	class leaf {
	public:
		leaf(float px, float py, float pSpeed, float pAngle) :enlargeRate(0), random(0) { 
			x = px; 
			y = py;
			speed = pSpeed; 
			angle = pAngle;
		}
		void draw() const { DrawRotaGraphF(x, y, enlargeRate, angle, Image::getIns()->getLeaf(), TRUE); }
		void setX(float px) { x = px; }
		void setY(float py) { y = py; }
		void setSpeed(float pSpeed) { speed = pSpeed; }
		void setAngle(float pAngle) { angle = pAngle; }
		void setEnlargeRate(float enlarge) { enlargeRate = enlarge; }
		void setRamdomNum(int rand) { random = rand; }
		float const getX() { return x; }
		float const getY() { return y; }
		float const getSpeed() { return speed; }
		float const getAngle() { return angle; }
		float const getRandom() { return random; }

	private:
		float x, y, speed, angle, enlargeRate;
		int random;
	};

	std::vector<leaf> leaves;
	void setLeaves(float x, float y, float speed, float angle);
	void updateLeaves();
};

