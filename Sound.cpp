#include "Sound.h"
#include <DxLib.h>

Sound::Sound() {
	/* sound for game play*/
	_hit = myLoadSound("../sound/hit.wav");
	ChangeVolumeSoundMem(50, _hit);
	_enemyShot = myLoadSound("../sound/enemy_shot.wav");
	ChangeVolumeSoundMem(70, _enemyShot);
	_bulletEffect = myLoadSound("../sound/effect_nc24120.wav");
	ChangeVolumeSoundMem(90, _bulletEffect);
	_spellCardEffect = myLoadSound("../sound/spellCard_nc3469.wav");
	ChangeVolumeSoundMem(90, _spellCardEffect);
	_bossDefeat = myLoadSound("../sound/boss_defeat.wav");
	ChangeVolumeSoundMem(90, _bossDefeat);
	_getHit = myLoadSound("../sound/getHit_nc130654.wav");
	ChangeVolumeSoundMem(50, _getHit);

	/* music for each stage*/
	_stage1 = myLoadSound("../sound/stage1_nc19205.mp3");
	ChangeVolumeSoundMem(150, _stage1);
	_stage1Boss = myLoadSound("../sound/ran_nc19283.mp3");
	ChangeVolumeSoundMem(150, _stage1Boss);

	/* sound for title scene*/
	_title = myLoadSound("../sound/title_nc133919.mp3");
	ChangeVolumeSoundMem(150, _title);
	_proceed = myLoadSound("../sound/proceed_nc129731.wav");
	ChangeVolumeSoundMem(70, _proceed);
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