#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>

#define FREQUENCY 48000
#define TONE 440
#define AMPLITUDE 7
#define BIAS 127
#define SAMPLES_PER_FRAME ((FREQUENCY / 60) * 3)

class Audio {
    private:
        SDL_AudioSpec audiospec;
        SDL_AudioDeviceID device;
        unsigned char *audio_buffer;

        double wave_position;
        double wave_increment; 

        void SineWave(int length);

    public:

        Audio();
        ~Audio();
        int Initialize();
        void Beep(int length);
};

#endif
