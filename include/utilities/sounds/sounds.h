#ifndef SOUNDS_H
#define SOUNDS_H

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <utilities/Singleton.hpp>
#define WAV_TEST "ressources/sounds/test.wav"

static Uint8 *audio_pos;
static Uint32 audio_len;
//TODO: Comment faire appel a la callback si function est dans la class
void my_audio_callback(void *userdata, Uint8 *stream, int len);

class Sounds : public Singleton<Sounds>
{
    friend class Singleton<Sounds>;

    private:
    Mix_Music *m_menu_music;
    Mix_Chunk *m_menu_click;

    public:

    Sounds();
    void initMixerAudio();
    void closeMixerAudio();
    void loadMusic(std::string music);
    void pauseMusic();
    void resumeMusic();
    void loadWav(std::string wavName);


};

#endif
