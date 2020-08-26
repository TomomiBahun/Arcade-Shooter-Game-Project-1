#include <DxLib.h>
#include "SystemMain.h"
#include "Define.h"
#include "Looper.h"

bool SystemMain::init() const
{
	SetAlwaysRunFlag(TRUE); // process even when the window is not active
	SetWindowSizeChangeEnableFlag(TRUE); // allow change in the windonw size
	SetOutApplicationLogValidFlag(FALSE); // no log will be saved
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP); // when full screen, maintain the window ratio
	SetWindowText("Project 1");
	ChangeWindowMode(TRUE); // enable the window mode
	const int COLOR_BIT = 32;
	SetGraphMode(Define::WIN_W, Define::WIN_H, COLOR_BIT);

	if (DxLib_Init()) {
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

void SystemMain::deInit() const
{
	DxLib_End();
}

void SystemMain::main() const
{
	Looper looper;
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		if (!looper.loop() || CheckHitKey(KEY_INPUT_ESCAPE)) { // ESCAPE condition is only for debugging
			break;
		}
	}
}