#include "S1ReimuConversation.h"
#include "Image.h"
#include "Define.h"
#include "keyboard.h"
#include <DxLib.h>

using namespace std;

const static float SHRINK = 0.5;
const static int BRIGHTNESS_MAX = 255;
const static int BRIGHTNESS_MIN = 130;

S1ReimuConversation::S1ReimuConversation() : _index(0), _counter(0), _canBossCome(false)
{
	reimuAndRan.push_back(""); // zero
	reimuAndRan.push_back("Reimu: Too many ghosts! Where are they coming from?"); // first
	reimuAndRan.push_back("Ran Yakumo: Oh, hi Reimu"); // second
	reimuAndRan.push_back("Reimu: What are you doing here?"); // third
	reimuAndRan.push_back("Ran: I am investigating this area for Lady Yukari.\n     She wants to know where ghosts are coming from.\n     I guess you are here for the same reason..."); // forth
	reimuAndRan.push_back("Reimu: There are so many ghosts around my shrine now!\n       It's impacting the shrine's business..."); // fifth
	reimuAndRan.push_back("Ran: By the way, Lady Yukari gave me one more command..."); // sixth
	reimuAndRan.push_back("Reimu: ?"); // seventh*/
	reimuAndRan.push_back("Ran: I'm here to eliminate anybody that I see in this area.\n     No matter if it is ghosts, monster, or human!!"); // eighth

	vector<int> zero = { NULL, NULL }; // dummy element. This won't be used.
	vector<int> first = { Image::getIns()->getReimuAngry(), NULL };
	vector<int> second = { Image::getIns()->getReimuNormal(), Image::getIns()->getRanNormal() };
	vector<int> third = { Image::getIns()->getReimuNormal(), Image::getIns()->getRanNormal() };
	vector<int> forth= { Image::getIns()->getReimuNormal(), Image::getIns()->getRanTired() };
	vector<int> fifth = { Image::getIns()->getReimuAngry(), Image::getIns()->getRanTired() };
	vector<int> sixth = { Image::getIns()->getReimuNormal(), Image::getIns()->getRanNormal() };
	vector<int> seventh = { Image::getIns()->getReimuNormal(), Image::getIns()->getRanNormal() };
	vector<int> eighth = { Image::getIns()->getReimuAngry(), Image::getIns()->getRanConfident() };
	imageReimuAndRan.push_back(zero); // dummy element. This won't be used
	imageReimuAndRan.push_back(first);
	imageReimuAndRan.push_back(second);
	imageReimuAndRan.push_back(third);
	imageReimuAndRan.push_back(forth);
	imageReimuAndRan.push_back(fifth);
	imageReimuAndRan.push_back(sixth);
	imageReimuAndRan.push_back(seventh);
	imageReimuAndRan.push_back(eighth);
}

bool S1ReimuConversation::update()
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

void S1ReimuConversation::draw() const
{
	/* draw Characters*/
	/* When index is even, Ran is speaking. When index is odd, Reimu is speaking */
	if (_index % 2 == 0) { // When Ran is speaking, Reimu's image should be dimmed
		SetDrawBright(BRIGHTNESS_MIN, BRIGHTNESS_MIN, BRIGHTNESS_MIN);
		DrawRotaGraphF(Define::IN_X + 100, Define::CENTER_Y + 200, SHRINK, 0, imageReimuAndRan[_index][0], TRUE); // Reimu
		SetDrawBright(BRIGHTNESS_MAX, BRIGHTNESS_MAX, BRIGHTNESS_MAX);
		DrawRotaGraphF(Define::INNER_W - 70, Define::CENTER_Y + 200, SHRINK, 0, imageReimuAndRan[_index][1], TRUE); // Ran
	}
	else { // When Reimu is speaking, Ran's image should be dimmed
		SetDrawBright(BRIGHTNESS_MIN, BRIGHTNESS_MIN, BRIGHTNESS_MIN);
		DrawRotaGraphF(Define::INNER_W - 70, Define::CENTER_Y + 200, SHRINK, 0, imageReimuAndRan[_index][1], TRUE); // Ran
		SetDrawBright(BRIGHTNESS_MAX, BRIGHTNESS_MAX, BRIGHTNESS_MAX);
		DrawRotaGraphF(Define::IN_X + 100, Define::CENTER_Y + 200, SHRINK, 0, imageReimuAndRan[_index][0], TRUE); // Reimu
	}

	/* draw message box*/
	DrawRotaGraphF(Define::CENTER_X, Define::CENTER_Y + 300, 1.0, 0, Image::getIns()->getMessagebox(), TRUE);
	DrawFormatString(Define::IN_X + 50, Define::CENTER_Y + 250, GetColor(255, 255, 255), reimuAndRan[_index]);
}