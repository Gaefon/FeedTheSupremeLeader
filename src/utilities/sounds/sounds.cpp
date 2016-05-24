#include <utilities/sounds/sounds.h>

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

int Sounds::test()	{
	return 0;
}
