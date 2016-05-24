#ifndef SOUNDS_H
#define SOUNDS_H

#include <iostream>
#include <SDL2/SDL.h>
#define WAV_TEST "ressources/sounds/test.wav"
// variable declarations
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play
  void my_audio_callback(void *userdata, Uint8 *stream, int len);

class Sounds
{
    public:

    Sounds();
    int init_audio();

    int test();

};

#endif
