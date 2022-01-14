#include "Platform/Platform.hpp"

#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

class SoundManager {
private:

	static bool classInitialized;

	SoundManager();
	~SoundManager();

	static bool isPlayingIntroMusic;
	static bool isPlayingBattleMusic;

	static sf::SoundBuffer MUSIC_INTRO;
	static sf::SoundBuffer MUSIC_BATTLE;

	static sf::SoundBuffer SOUND_FIRE_SHOT;
	static sf::SoundBuffer SOUND_TANK_SHOT;
	static sf::SoundBuffer SOUND_BOX_DESTROYED;
	static sf::SoundBuffer SOUND_TANK_ONE_DRIVING;
	static sf::SoundBuffer SOUND_TANK_TWO_DRIVING;
	static sf::SoundBuffer SOUND_ITEM_PICKED;
	static sf::SoundBuffer SOUND_BUTTON_PRESSED;
	static sf::SoundBuffer SOUND_WIN;
	static sf::SoundBuffer SOUND_VICTORY;
	static sf::SoundBuffer SOUND_LAVA_TOUCHED;

	static std::vector<sf::Sound> sounds;
	static sf::Sound introMusic;
	static sf::Sound battleMusic;

	static float musicVolume;
	static float soundVolume;

	static void CheckInitialization();
	static void Clear();
	static sf::SoundBuffer* GetBufferPtr(int type);

public:

	static const int TYPE_FIRE_SHOT = 0;
	static const int TYPE_TANK_SHOT = 1;
	static const int TYPE_BOX_DESTROYED = 2;
	static const int TYPE_TANK_ONE_DRIVING = 3;
	static const int TYPE_TANK_TWO_DRIVING = 4;
	static const int TYPE_ITEM_PICKED = 5;
	static const int TYPE_BUTTON_PRESSED = 6;
	static const int TYPE_WIN = 7;
	static const int TYPE_VICTORY = 8;
	static const int TYPE_LAVA_TOUCHED = 9;

	static void Init();

	static void KillSound(int type);
	static void ToggleIntroMusic();
	static void ToggleBattleMusic();
	static void PlaySoundEffect(int type);
};

#endif