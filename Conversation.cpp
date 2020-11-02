#include "Conversation.h"
#include "Image.h"
#include "Define.h"
#include "keyboard.h"
#include <DxLib.h>

using namespace std;

const static float SHRINK = 0.5;

Conversation::Conversation() : _index(0), _counter(0), _canBossCome(false)
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
	vector<int> second = { Image::getIns()->getReimuNormalLayered(), Image::getIns()->getRanNormal() };
	vector<int> third = { Image::getIns()->getReimuNormal(), Image::getIns()->getRanNormalLayered() };
	vector<int> forth= { Image::getIns()->getReimuNormalLayered(), Image::getIns()->getRanTired() };
	vector<int> fifth = { Image::getIns()->getReimuAngry(), Image::getIns()->getRanTiredLayered() };
	vector<int> sixth = { Image::getIns()->getReimuNormalLayered(), Image::getIns()->getRanNormal() };
	vector<int> seventh = { Image::getIns()->getReimuNormal(), Image::getIns()->getRanNormalLayered() };
	vector<int> eighth = { Image::getIns()->getReimuAngryLayered(), Image::getIns()->getRanConfident() };
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
	DrawFormatString(Define::IN_X + 50, Define::CENTER_Y + 250, GetColor(255, 255, 255), reimuAndRan[_index]);
}