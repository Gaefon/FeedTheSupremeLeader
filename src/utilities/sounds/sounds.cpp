#include <utilities/sounds/sounds.h>
#include <Constants.hpp>

using namespace std;

/**
* @constructor Sounds
**/
Sounds::Sounds()
{
}

/**
* @function initMixerAudio
* @description initialisation de SDL Mixer
* int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize)
* MIX_DEFAULT_FREQUENCY = 22050, on va utiliser 44100 pour avoir une meilleur qualité
* MIX_DEFAULT_CHANNELS = Stéréo
**/
void Sounds::initMixerAudio()
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
	{
		cerr << Mix_GetError() << endl;
	}
}

/**
* @function closeMixerAudio
* Fermeture de la SDL_mixer
**/
void Sounds::closeMixerAudio()
{
	Mix_FreeMusic(m_menu_music);
	Mix_CloseAudio();
}

void Sounds::loadMusic(string music)
{
	m_menu_music = Mix_LoadMUS(music.c_str());
	Mix_PlayMusic(m_menu_music, -1);
}

void Sounds::pauseMusic()
{
	Mix_PauseMusic();
}

void Sounds::resumeMusic()
{
	Mix_ResumeMusic();
}

void Sounds::loadWav(string wavName)
{
	m_menu_click = Mix_LoadWAV(wavName.c_str());
	Mix_VolumeChunk(m_menu_click, MIX_MAX_VOLUME);
	Mix_PlayChannel(1, m_menu_click, 0);
}
