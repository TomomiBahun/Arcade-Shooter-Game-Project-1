#include "S1MarisaConversation.h"
#include "Image.h"
#include "Define.h"
#include "keyboard.h"
#include <DxLib.h>

using namespace std;

const static float SHRINK = 0.5;
const static int BRIGHTNESS_MAX = 255;
const static int BRIGHTNESS_MIN = 130;

S1MarisaConversation::S1MarisaConversation() : _index(0), _counter(0), _canBossCome(false)
{
	marisaAndRan.push_back(""); // zero
	marisaAndRan.push_back("Marisa: Wow, there are so many ghosts in the forest!\n        Something interesting must be happening in this area...\n        I should go find out what's going on."); // first
	marisaAndRan.push_back("Ran Yakumo: Hey human, you shouldn't be out here now. You saw ghosts, right?"); // second
	marisaAndRan.push_back("Marisa: Yukari's fox! Are you the one who's letting the ghosts come out?"); // third
	marisaAndRan.push_back("Ran: No, I am investigating this forest for Lady Yukari.\n     She wants to know where the ghosts are coming from."); // forth
	marisaAndRan.push_back("Marisa: Okay, then. Bye!\n        Let me know what you find out about this mystery when I come back."); // fifth
	marisaAndRan.push_back("Ran: No! I can't let you go yet!\n     Lady Yukari gave me one more command."); // sixth
	marisaAndRan.push_back("Marisa: ?"); // seventh*/
	marisaAndRan.push_back("Ran: I'm here to eliminate anybody that I see in this area.\n     No matter if it is ghosts, monster, or human!!"); // eighth

	vector<int> zero = { NULL, NULL }; // dummy element. This won't be used.
	vector<int> first = { Image::getIns()->getMarisaHappy(), NULL };
	vector<int> second = { Image::getIns()->getMarisaHappy(), Image::getIns()->getRanNormal() };
	vector<int> third = { Image::getIns()->getMarisaSmile(), Image::getIns()->getRanNormal() };
	vector<int> forth = { Image::getIns()->getMarisaSmile(), Image::getIns()->getRanTired() };
	vector<int> fifth = { Image::getIns()->getMarisaHappy(), Image::getIns()->getRanTired() };
	vector<int> sixth = { Image::getIns()->getMarisaSmile(), Image::getIns()->getRanNormal() };
	vector<int> seventh = { Image::getIns()->getMarisaSmile(), Image::getIns()->getRanNormal() };
	vector<int> eighth = { Image::getIns()->getMarisaCreepy(), Image::getIns()->getRanConfident() };
	imageMarisaAndRan.push_back(zero); // dummy element. This won't be used
	imageMarisaAndRan.push_back(first);
	imageMarisaAndRan.push_back(second);
	imageMarisaAndRan.push_back(third);
	imageMarisaAndRan.push_back(forth);
	imageMarisaAndRan.push_back(fifth);
	imageMarisaAndRan.push_back(sixth);
	imageMarisaAndRan.push_back(seventh);
	imageMarisaAndRan.push_back(eighth);
}

bool S1MarisaConversation::update()
{
	_counter++;
	// start the conversation without checking keyboard input first
	if (_index == 0 || Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {
		_index++;
	}
	if (_index == 2) { // after a certain point of the conversation, let the boss icon come in the game board
		_canBossCome = true;
	}
	if (_index == imageMarisaAndRan.size()) {
		return false; // if the conversation is done, return false
	}
	return true; // if the conversation is still going, return true
}

void S1MarisaConversation::draw() const
{
	/* draw Characters*/
	/* When index is even, Ran is speaking. When index is odd, Marisa is speaking */
	if (_index % 2 == 0) { // When Ran is speaking, Marisa's image should be dimmed
		SetDrawBright(BRIGHTNESS_MIN, BRIGHTNESS_MIN, BRIGHTNESS_MIN);
		DrawRotaGraphF(Define::IN_X + 130, Define::CENTER_Y + 200, SHRINK, 0, imageMarisaAndRan[_index][0], TRUE); // Marisa
		SetDrawBright(BRIGHTNESS_MAX, BRIGHTNESS_MAX, BRIGHTNESS_MAX);
		DrawRotaGraphF(Define::INNER_W - 70, Define::CENTER_Y + 200, SHRINK, 0, imageMarisaAndRan[_index][1], TRUE); // Ran
	}
	else { // When Marisa is speaking, Ran's image should be dimmed
		SetDrawBright(BRIGHTNESS_MIN, BRIGHTNESS_MIN, BRIGHTNESS_MIN);
		DrawRotaGraphF(Define::INNER_W - 70, Define::CENTER_Y + 200, SHRINK, 0, imageMarisaAndRan[_index][1], TRUE); // Ran
		SetDrawBright(BRIGHTNESS_MAX, BRIGHTNESS_MAX, BRIGHTNESS_MAX);
		DrawRotaGraphF(Define::IN_X + 130, Define::CENTER_Y + 200, SHRINK, 0, imageMarisaAndRan[_index][0], TRUE); // Marisa
	}

	/* draw message box*/
	DrawRotaGraphF(Define::CENTER_X, Define::CENTER_Y + 300, 1.0, 0, Image::getIns()->getMessagebox(), TRUE);
	DrawFormatString(Define::IN_X + 50, Define::CENTER_Y + 250, GetColor(255, 255, 255), marisaAndRan[_index]);
}