#include "Sound.h"
#include <DxLib.h>

Sound::Sound() {
	_hit = myLoadSound("../sound/hit.wav");
	ChangeVolumeSoundMem(70, _hit);
	_enemyShot = myLoadSound("../sound/enemy_shot.wav");
	ChangeVolumeSoundMem(70, _enemyShot);
	_bulletEffect = myLoadSound("../sound/effect_nc24120.wav");
	ChangeVolumeSoundMem(90, _bulletEffect);
	_spellCardEffect = myLoadSound("../sound/spellCard_nc3469.wav");
	ChangeVolumeSoundMem(90, _spellCardEffect);
	_getHit = myLoadSound("../sound/getHit_nc130654.wav");
	ChangeVolumeSoundMem(50, _getHit);
	_title = myLoadSound("../sound/title_nc133919.mp3");
	ChangeVolumeSoundMem(150, _title);
	_stage1 = myLoadSound("../sound/stage1_nc19205.mp3");
	ChangeVolumeSoundMem(150, _stage1);
	_stage1Boss = myLoadSound("../sound/ran_nc19283.mp3");
	ChangeVolumeSoundMem(150, _stage1Boss);

}

void Sound::release()
{
	const int size = _sound.size();
	for (int i = 0; i < size; i++) {
		DeleteMusicMem(_sound[i]);
	}
	_sound.clear();
}

int Sound::myLoadSound(const char* fileName)
{
	int ret = LoadSoundMem(fileName);
	_sound.push_back(ret);
	return ret;
}