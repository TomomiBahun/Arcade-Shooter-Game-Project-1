#pragma once

class Define final {
public:
	const static int WIN_W;
	const static int WIN_H;

	const static int OUTER_W;
	const static int OUTER_H;
	const static int INNER_W;
	const static int INNER_H;
	const static int CENTER_X;
	const static int CENTER_Y;
	const static int IN_X;
	const static int IN_Y;

	const static float PI;

	enum eStage {
		stage1 = 1,
		stage2,
		stage3,
		stage4,
		stage5,
		stageEX,
		stageNum,
	};

	enum eLevel {
		easy = 1,
		normal,
		levelNum,
	};
};