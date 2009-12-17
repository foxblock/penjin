#ifndef SOUND_H
#define SOUND_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <string>
#include "PenjinTypes.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;
using namespace std;

namespace SoundClass
{
    void init();
    void deInit();
}

class Sound
{
    public:
        Sound();
        ~Sound();

        PENJIN_ERRORS loadSound(CRstring soundName);
        void setLoops(CRint loops){this->loops = loops;}
        void setVolume(CRuint volume){Mix_Volume(channel,volume);}
        uint getVolume()const{return Mix_Volume(channel,-1);}
        void setGlobalVolume(CRuint volume){Mix_Volume(-1,volume);}
        uint getGlobalVolume()const{return Mix_Volume(-1,-1);}

        bool isPlaying()const;
        bool isPaused()const;

        void play();
        void pause();
        void playPause();
        void stop();
        void stopAll();

        void freeAll();
    private:
        Mix_Chunk *sound;
        int channel;
        int loops;
};
#endif	//	SOUND_H
