#include <utilities/sounds/sounds.h>

using namespace std;

/**
* @constructor Sounds
**/
Sounds::Sounds()	{
}

/**
* @function init_audio
* @description
* @return {void}
**/
int Sounds::init_audio() {
	static Uint32 wav_length;
	static Uint8 *wav_buffer;
	static SDL_AudioSpec wav_spec;

	if(SDL_LoadWAV(WAV_TEST, &wav_spec, &wav_buffer, &wav_length) == NULL) {
		fprintf(stderr, "Couldn't load wav: %s\n", SDL_GetError());
	  return -1;
	}
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
	audio_pos = wav_buffer;
	audio_len = wav_length;

	if (SDL_OpenAudio(&wav_spec, NULL) < 0){
	  fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
	  return -1;
	}

	SDL_PauseAudio(0);

	while (audio_len > 0) {
	//	SDL_Delay(2000);
	}

	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);
	return(0);
}

/**
* @function my_audio_callback
* @description
* @return {void}
**/
void my_audio_callback(void *userdata, Uint8 *stream, int len) {
	if (audio_len == 0)
		return;
	len = (len > audio_len ? audio_len : len);
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
	audio_pos += len;
	audio_len -= len;
}

/**
* @function initMixerAudio
* @description initialisation de SDL Mixer
* int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize)
* MIX_DEFAULT_FREQUENCY = 22050, on va utiliser 44100 pour avoir une meilleur qualité
* MIX_DEFAULT_CHANNELS = Stéréo
**/
void Sounds::initMixerAudio() {
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
}

/**
* @function closeMixerAudio
* Fermeture de la SDL_mixer
**/
void Sounds::closeMixerAudio() {
	Mix_FreeMusic(m_menu_music);
	Mix_CloseAudio();
}

void Sounds::loadMusic() {
	m_menu_music = Mix_LoadMUS("ressources/sounds/menu.mp3");
  Mix_PlayMusic(m_menu_music, -1);
}

void Sounds::pauseMusic()	{
	Mix_PauseMusic();
}

void Sounds::resumeMusic() {
	Mix_ResumeMusic();
}

void Sounds::loadWav(char *wavName) {
	m_menu_click = Mix_LoadWAV(wavName);
	Mix_VolumeChunk(m_menu_click, MIX_MAX_VOLUME);
	Mix_PlayChannel(1, m_menu_click, 0);
}
