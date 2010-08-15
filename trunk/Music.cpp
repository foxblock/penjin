#include "Music.h"

Music::Music()
{
	music = NULL;
	numLoops = -1;	// default loop forever;
	playPos = 0;
}

Music::~Music()
{
	freeAll();
}

void Music::freeAll()
{
	if(music)
	{
	    if (isPaused())
            Mix_ResumeMusic();
        Mix_HaltMusic();
		Mix_FreeMusic(music);				// Release the memory allocated to music
		music = NULL;
	}
}

PENJIN_ERRORS Music::loadMusic(CRstring musicFile)
{
	freeAll();
	music = Mix_LoadMUS(musicFile.c_str());
	if(music)
		return PENJIN_OK;
	return PENJIN_FILE_NOT_FOUND;
}

bool Music::isPlaying()const
{
	if(Mix_PlayingMusic() == 1)
		return true;
	return false;
}

bool Music::isPaused()const
{
	if(Mix_PausedMusic())
		return true;
	return false;
}

void Music::pause()
{
	if(isPlaying())
		Mix_PauseMusic();
    timer.pause();
}

void Music::playPause()
{
    if(isPaused())
        play();
    else if(isPlaying())
        pause();
}

void Music::play()
{
	if(!isPaused())
		Mix_PlayMusic(music, numLoops);	// Play the music
	else
		Mix_ResumeMusic();
    timer.unpause();
}

void Music::playFadeIn(CRuint milliseconds)
{
    if(!isPaused())
        Mix_FadeInMusic(music, numLoops, milliseconds);
    else
        Mix_ResumeMusic();
    timer.unpause();
}

void Music::stop()
{
    if(isPlaying())
        Mix_HaltMusic();
    timer.stop();
}

void Music::fade(CRint ms)
{
	Mix_FadeOutMusic((int)ms);
}

void Music::setLooping(CRbool looping)
{
	if(looping)
		numLoops = -1;
	else
		numLoops = 1;
}

void Music::setLooping(CRint numLoops)
{
	this->numLoops = numLoops;
}

void Music::setVolume(CRuint volume)
{
	Mix_VolumeMusic(volume);
}

void Music::setPlayPosition(CRint ms)
{
    rewind();
    Mix_SetMusicPosition(ms*0.001f);
    playPos = ms;
}
