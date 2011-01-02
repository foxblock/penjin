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
#ifndef MUSIC_H
#define MUSIC_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <string>
#include "PenjinTypes.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;
using namespace std;
#include "Timer.h"

class Music
{
public:
	Music();
	~Music();

	PENJIN_ERRORS loadMusic(CRstring musicFile);

	bool isPlaying()const;
	bool isPaused()const;

	void play();
    void playFadeIn(CRuint milliseconds);
	void pause();
	void playPause();
	void stop();
	void fade(CRint ms);
    void rewind(){Mix_RewindMusic();}
	void setLooping(CRbool looping);
	void setLooping(CRint numLoops);

	void setVolume(CRuint volume);
	uint getVolume()const{return Mix_VolumeMusic(-1);}

	void setPlayPosition(CRint ms);
	int getPlayPosition(){return timer.getScaledTicks() + playPos;}

	void freeAll();
private:
	Mix_Music *music;
	int numLoops;

	Timer timer;
	int playPos;
};
#endif	//	MUSIC_H
