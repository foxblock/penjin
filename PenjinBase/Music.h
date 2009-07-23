#ifndef MUSIC_H
#define MUSIC_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <string>
#include "PenjinTypes.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;
using namespace std;

class Music
{
public:
	Music();
	~Music();

	PENJIN_ERRORS loadMusic(CRstring musicFile);

	bool isPlaying()const;
	bool isPaused()const;

	void play();
	void pause();
	void playPause();
	void stop();
	void fade(CRint ms);

	void setLooping(CRbool looping);
	void setLooping(CRint numLoops);

	void setVolume(CRuint volume);
	uint getVolume()const{return Mix_VolumeMusic(-1);};

	void freeAll();
private:
	Mix_Music *music;
	int numLoops;
};
#endif	//	MUSIC_H
