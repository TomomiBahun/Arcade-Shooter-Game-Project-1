#include "EndConversation.h"
#include "Image.h"
#include "Define.h"
#include "keyboard.h"
#include <DxLib.h>

using namespace std;

const static float SHRINK = 0.5;

EndConversation::EndConversation() : _index(0), _counter(0), _flag(false)
{
	reimuAndRan.push_back(""); // zero
	reimuAndRan.push_back("Reimu: Your master must know what is going on.\n       Go get her now."); // first
	reimuAndRan.push_back("Ran: No, Lady Yukari is sleeping.\n     Ahh I should go back home, so she can fix me."); // second
	reimuAndRan.push_back("Reimu: The servant caused me trouble.\n       I feel like Yukari should help me first..."); // third
	reimuAndRan.push_back("Ran: She won't get up until midnight.\n     There is a witch living in this forest. You should go to her house."); // forth
	reimuAndRan.push_back("Reimu: Well, I guess I can do that too.\n       I didn't want to go further into the forest though."); // fifth
	reimuAndRan.push_back(""); //sixth ... stage clear

	vector<int> zero = { NULL, NULL }; // dummy element. This won't be used.
	vector<int> first = { Image::getIns()->getReimuSmile(), Image::getIns()->getRanCryingLayered() };
	vector<int> second = { Image::getIns()->getReimuSmileLayered(), Image::getIns()->getRanCrying() };
	vector<int> third = { Image::getIns()->getReimuCreepy(), Image::getIns()->getRanCryingLayered() };
	vector<int> forth= { Image::getIns()->getReimuCreepyLayered(), Image::getIns()->getRanTired() };
	vector<int> fifth = { Image::getIns()->getReimuConfused(), Image::getIns()->getRanTiredLayered() };
	vector<int> sixth = { Image::getIns()->getStageClear(), NULL };
	imageReimuAndRan.push_back(zero); // dummy element. This won't be used
	imageReimuAndRan.push_back(first);
	imageReimuAndRan.push_back(second);
	imageReimuAndRan.push_back(third);
	imageReimuAndRan.push_back(forth);
	imageReimuAndRan.push_back(fifth);
	imageReimuAndRan.push_back(sixth);
}

bool EndConversation::update()
{
	_counter++;
	// start the conversation without checking keyboard input first
	if (_index == 0 || Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {
		_index++;
	}
	if (_index == imageReimuAndRan.size()) {
		_flag = true; // when this flag is true, the conversation is done
		return false; // if the conversation is done, return false
	}
	return true; // if the conversation is still going, return true
}

void EndConversation::draw() const
{
	if (_index < 6) {
		/* draw Characters*/
		DrawRotaGraphF(Define::IN_X + 100, Define::CENTER_Y + 200, SHRINK, 0, imageReimuAndRan[_index][0], TRUE);
		DrawRotaGraphF(Define::INNER_W - 70, Define::CENTER_Y + 200, SHRINK, 0, imageReimuAndRan[_index][1], TRUE);

		/* draw message box*/
		DrawRotaGraphF(Define::CENTER_X, Define::CENTER_Y + 300, 1.0, 0, Image::getIns()->getMessagebox(), TRUE);
		DrawFormatString(Define::IN_X + 50, Define::CENTER_Y + 250, GetColor(255, 255, 255), reimuAndRan[_index]);
	}
	else {
		DrawRotaGraphF(Define::CENTER_X, Define::CENTER_Y, 1.0, 0, imageReimuAndRan[_index][0], TRUE);
	}
}