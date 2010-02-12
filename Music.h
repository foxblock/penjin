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
