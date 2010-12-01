/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef SOUND_H
#define SOUND_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <string>
#include <vector>
#include "PenjinTypes.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;
using namespace std;

namespace SoundClass
{
    void init();
    void deInit();
    void setGlobalVolume(CRuint volume);
    uint getGlobalVolume();
    void stopAll();
}

class Sound
{
    public:
        Sound();
        ~Sound();

        PENJIN_ERRORS loadSound(CRstring soundName);
        void setLoops(CRint newloops, CRint id=-1){this->defLoops = newloops;}; // set default loops, which will be used when play is called without loop parameter
        void setVolume(CRuint volume, CRint id=-1); // using -1 as id will set volume for all playing instances
        uint getVolume(CRint id=-1)const; // using -1 as id will return volume for first instance
        void setSimultaneousPlay(CRbool b){simultaneousPlay = b;} // allow playing of multiple instances of this sound as the same time

        bool isPlaying(CRint id=-1)const; // no or id=-1 will return first instance's status
        bool isPaused(CRint id=-1)const; // no or id=-1 will return first instance's status

        void play(int loops=-2, CRint id=-1); // passing a loop parameter will overwrite the default value for this instance, passing -1 as id will add another instance to the list (if simul play is true)
        void pause(CRint id=-1); // pauses all instances if id is -1
        void playPause(CRint id=-1); // only plays/pauses one instance, first one of id is -1
        void stop(CRint id=-1); // stops all instances if id is -1

        void freeAll();
    private:
        Mix_Chunk *sound;
        bool simultaneousPlay;
        int defLoops;
        vector< pair<int, int> > instances; // channel, loops
};
#endif	//	SOUND_H
