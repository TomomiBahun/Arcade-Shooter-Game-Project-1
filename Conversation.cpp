#include "Conversation.h"
#include "Image.h"
#include "Define.h"
#include "keyboard.h"
#include <DxLib.h>

using namespace std;

const static float SHRINK = 0.5;

Conversation::Conversation() : _index(0), _counter(0), _canBossCome(false)
{
	reimuAndRan.push_back("");
	reimuAndRan.push_back("Reimu: too many ghosts! where are they coming from?");
	reimuAndRan.push_back("Ran: Oh hi Reimu");
	reimuAndRan.push_back("Reimu: what are you doing here?");

	vector<int> zero = { NULL, NULL };
	vector<int> first = { Image::getIns()->getReimuNormal(), NULL };
	vector<int> second = { Image::getIns()->getReimuNormalLayered(), Image::getIns()->getRanNormal() };
	vector<int> third = { Image::getIns()->getReimuNormal(), Image::getIns()->getRanNormalLayered() };
	imageReimuAndRan.push_back(zero);
	imageReimuAndRan.push_back(first);
	imageReimuAndRan.push_back(second);
	imageReimuAndRan.push_back(third);
}

bool Conversation::update()
{
	_counter++;
	// start the conversation without checking keyboard input first
	if (_index == 0 || Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {
		_index++;
	}
	if (_index == 2) { // after a certain point of the conversation, let the boss icon come in the game board
		_canBossCome = true;
	}
	if (_index == imageReimuAndRan.size()) {
		return false; // if the conversation is done, return false
	}
	return true; // if the conversation is still going, return true
}

void Conversation::draw() const
{
	/* draw Characters*/
	DrawRotaGraphF(Define::IN_X+100, Define::CENTER_Y + 200, SHRINK, 0, imageReimuAndRan[_index][0], TRUE);
	DrawRotaGraphF(Define::INNER_W - 70, Define::CENTER_Y + 200, SHRINK, 0, imageReimuAndRan[_index][1], TRUE);

	/* draw message box*/
	DrawRotaGraphF(Define::CENTER_X, Define::CENTER_Y + 300, 1.0, 0, Image::getIns()->getMessagebox(), TRUE);
	DrawFormatString(Define::IN_X+100, Define::CENTER_Y + 250, GetColor(255, 255, 255), reimuAndRan[_index]);
}