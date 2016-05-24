#ifndef SOUNDS_H
#define SOUNDS_H

#include <iostream>
#include <SDL2/SDL.h>
#define WAV_TEST "ressources/sounds/test.wav"

static Uint8 *audio_pos;
static Uint32 audio_len;
//TODO: Comment faire appel a la callback si function est dans la class
void my_audio_callback(void *userdata, Uint8 *stream, int len);

class Sounds
{
    public:

    Sounds();
    int init_audio();

    int test();

};

#endif
