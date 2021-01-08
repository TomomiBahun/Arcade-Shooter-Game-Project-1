#include "S1MarisaEndConversation.h"
#include "Image.h"
#include "Define.h"
#include "keyboard.h"
#include <DxLib.h>

using namespace std;

const static float SHRINK = 0.5;
const static int BRIGHTNESS_MIN = 130;
const static int BRIGHTNESS_MAX = 255;

S1MarisaEndConversation::S1MarisaEndConversation() : _index(0), _counter(0), _flag(false)
{
	marisaAndRan.push_back(""); // zero
	marisaAndRan.push_back("Marisa: I didn't know Yukari is involved.\n        This ghost mystery might be more interesting than I expected."); // first
	marisaAndRan.push_back("Ran: Your magic hurts a lot! Ahh, I should go back home."); // second
	marisaAndRan.push_back("Marisa: Hey, what is Yukari trying to find out?\n        Why are you kicking people out of here?"); // third
	marisaAndRan.push_back("Ran: I don't know. She doesn't tell me a lot about the plan.\n     She gives me commands but I don't really care about the reasoning for them."); // forth
	marisaAndRan.push_back("Marisa: Hmm, okay.\n        I guess I can go visit my neighbor to find out more..."); // fifth
	marisaAndRan.push_back(""); //sixth ... stage clear

	vector<int> zero = { NULL, NULL }; // dummy element. This won't be used.
	vector<int> first = { Image::getIns()->getMarisaSmile(), Image::getIns()->getRanCrying() };
	vector<int> second = { Image::getIns()->getMarisaSmile(), Image::getIns()->getRanCrying() };
	vector<int> third = { Image::getIns()->getMarisaSmile(), Image::getIns()->getRanCrying() };
	vector<int> forth = { Image::getIns()->getMarisaCreepy(), Image::getIns()->getRanTired() };
	vector<int> fifth = { Image::getIns()->getMarisaSmile(), Image::getIns()->getRanTired() };
	vector<int> sixth = { Image::getIns()->getStageClear(), NULL };
	imageMarisaAndRan.push_back(zero); // dummy element. This won't be used
	imageMarisaAndRan.push_back(first);
	imageMarisaAndRan.push_back(second);
	imageMarisaAndRan.push_back(third);
	imageMarisaAndRan.push_back(forth);
	imageMarisaAndRan.push_back(fifth);
	imageMarisaAndRan.push_back(sixth);
}

bool S1MarisaEndConversation::update()
{
	_counter++;
	// start the conversation without checking keyboard input first
	if (_index == 0 || Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {
		_index++;
	}
	if (_index == imageMarisaAndRan.size()) {
		_flag = true; // when this flag is true, the conversation is done
		return false; // if the conversation is done, return false
	}
	return true; // if the conversation is still going, return true
}

void S1MarisaEndConversation::draw() const
{
	if (_index < 6) {
		/* draw Characters*/

		/* When index is even, Ran is speaking. When index is odd, Reimu is speaking */
		if (_index % 2 == 0) { // When Ran is speaking, Reimu's image should be dimmed
			SetDrawBright(BRIGHTNESS_MIN, BRIGHTNESS_MIN, BRIGHTNESS_MIN);
			DrawRotaGraphF(Define::IN_X + 130, Define::CENTER_Y + 200, SHRINK, 0, imageMarisaAndRan[_index][0], TRUE); // Reimu
			SetDrawBright(BRIGHTNESS_MAX, BRIGHTNESS_MAX, BRIGHTNESS_MAX);
			DrawRotaGraphF(Define::INNER_W - 70, Define::CENTER_Y + 200, SHRINK, 0, imageMarisaAndRan[_index][1], TRUE); // Ran
		}
		else { // When Reimu is speaking, Ran's image should be dimmed
			SetDrawBright(BRIGHTNESS_MIN, BRIGHTNESS_MIN, BRIGHTNESS_MIN);
			DrawRotaGraphF(Define::INNER_W - 70, Define::CENTER_Y + 200, SHRINK, 0, imageMarisaAndRan[_index][1], TRUE); // Ran
			SetDrawBright(BRIGHTNESS_MAX, BRIGHTNESS_MAX, BRIGHTNESS_MAX);
			DrawRotaGraphF(Define::IN_X + 130, Define::CENTER_Y + 200, SHRINK, 0, imageMarisaAndRan[_index][0], TRUE); // Reimu
		}

		/* draw message box*/
		DrawRotaGraphF(Define::CENTER_X, Define::CENTER_Y + 300, 1.0, 0, Image::getIns()->getMessagebox(), TRUE);
		DrawFormatString(Define::IN_X + 50, Define::CENTER_Y + 250, GetColor(255, 255, 255), marisaAndRan[_index]);
	}
	else {
		DrawRotaGraphF(Define::CENTER_X, Define::CENTER_Y, 1.0, 0, imageMarisaAndRan[_index][0], TRUE);
	}
}