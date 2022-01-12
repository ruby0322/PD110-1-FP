#include "SoundManager.hpp"

bool SoundManager::classInitialized = false;
bool SoundManager::isPlayingIntroMusic = false;
bool SoundManager::isPlayingBattleMusic = false;

float SoundManager::musicVolume = 18.f;
float SoundManager::soundVolume = 70.f;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

std::vector<sf::Sound> SoundManager::sounds;
sf::Sound SoundManager::introMusic;
sf::Sound SoundManager::battleMusic;

sf::SoundBuffer SoundManager::MUSIC_INTRO;
sf::SoundBuffer SoundManager::MUSIC_BATTLE;
sf::SoundBuffer SoundManager::SOUND_FIRE_SHOT;
sf::SoundBuffer SoundManager::SOUND_TANK_SHOT;
sf::SoundBuffer SoundManager::SOUND_BOX_DESTROYED;
sf::SoundBuffer SoundManager::SOUND_TANK_ONE_DRIVING;
sf::SoundBuffer SoundManager::SOUND_TANK_TWO_DRIVING;

void SoundManager::Init() {
	MUSIC_INTRO.loadFromFile("content/Audio/introMusic.wav");
	MUSIC_BATTLE.loadFromFile("content/Audio/battleMusic.wav");
	SOUND_FIRE_SHOT.loadFromFile("content/Audio/fireShot.wav");
	SOUND_TANK_SHOT.loadFromFile("content/Audio/tankShot.wav");
	SOUND_BOX_DESTROYED.loadFromFile("content/Audio/boxDestroyed.wav");
	SOUND_TANK_ONE_DRIVING.loadFromFile("content/Audio/tankDriving.wav");
	SOUND_TANK_TWO_DRIVING.loadFromFile("content/Audio/tankDriving.wav");

	introMusic.setBuffer(MUSIC_INTRO);
	battleMusic.setBuffer(MUSIC_BATTLE);
	introMusic.setLoop(true);
	battleMusic.setLoop(true);
	introMusic.setVolume(SoundManager::musicVolume);
	battleMusic.setVolume(SoundManager::musicVolume);

	SoundManager::classInitialized = true;
}

sf::SoundBuffer* SoundManager::GetBufferPtr(int type) {
	switch (type) {
		case SoundManager::TYPE_FIRE_SHOT:
		return &SoundManager::SOUND_FIRE_SHOT;
		break;
		case SoundManager::TYPE_TANK_SHOT:
		return &SoundManager::SOUND_TANK_SHOT;
		break;
		case SoundManager::TYPE_BOX_DESTROYED:
		return &SoundManager::SOUND_BOX_DESTROYED;
		break;
		case SoundManager::TYPE_TANK_ONE_DRIVING:
		return &SoundManager::SOUND_TANK_ONE_DRIVING;
		break;
		case SoundManager::TYPE_TANK_TWO_DRIVING:
		return &SoundManager::SOUND_TANK_TWO_DRIVING;
		break;
		default:
		return nullptr;
		break;
	}
}

void SoundManager::Clear() {
	for (size_t i = 0; i < SoundManager::sounds.size(); ++i)
		if (SoundManager::sounds[i].getStatus() == sf::Sound::Status::Stopped) {
			SoundManager::sounds.erase(SoundManager::sounds.begin() + i);
			--i;
		}
}

void SoundManager::KillSound(int type) {
	sf::SoundBuffer* targetBufferPtr = SoundManager::GetBufferPtr(type);
	for (size_t i = 0; i < SoundManager::sounds.size(); ++i)
		if (SoundManager::sounds[i].getBuffer() == targetBufferPtr) {
			SoundManager::sounds.erase(SoundManager::sounds.begin() + i);
			--i;
		}
}

void SoundManager::CheckInitialization() {
	if (!SoundManager::classInitialized)
		SoundManager::Init();
}

void SoundManager::ToggleIntroMusic()
{
	CheckInitialization();
	SoundManager::isPlayingIntroMusic = !SoundManager::isPlayingIntroMusic;
	if (SoundManager::isPlayingIntroMusic)
	{
		SoundManager::introMusic.play();
	}
	else
	{
		SoundManager::introMusic.pause();
	}
}

void SoundManager::ToggleBattleMusic()
{
	CheckInitialization();
	SoundManager::isPlayingBattleMusic = !SoundManager::isPlayingBattleMusic;
	if (SoundManager::isPlayingBattleMusic)
	{
		SoundManager::battleMusic.play();
	}
	else
	{
		SoundManager::battleMusic.pause();
	}
}

void SoundManager::PlaySoundEffect(int type) {
	CheckInitialization();
	if (0 <= type && type <= 4) {
		sf::Sound sound;
		sound.setBuffer(*SoundManager::GetBufferPtr(type));
		sound.setVolume(SoundManager::soundVolume);
		SoundManager::sounds.push_back(sound);
		SoundManager::sounds.back().play();
	}
}