#include "Sound.h"

Sound::Sound()
{
	sound = NULL;
	channel = -1;
	loops = 0;
}

void SoundClass::init()
{
	#ifdef PLATFORM_GP2X
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 128);			// Initialize SDL_mixer for GP2X, buffer is set lower than PC
    #elif PLATFORM_PC
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 512);		// Initialize SDL_mixer for PC, buffer is set higher
    #elif PLATFORM_PANDORA
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 512);
	#else
        #error "Audio setup is not defined for this platform!"
	#endif
}

void SoundClass::deInit()
{
	Mix_CloseAudio();																// Close SDL_Mixer Audio
}

Sound::~Sound()
{
	freeAll();
}

void Sound::freeAll()
{
	if(sound)
	{
	    if(isPlaying())
            stop();
		Mix_FreeChunk(sound);															// Release the memory allocated to sound
		sound = NULL;
	}
	sound = NULL;
	channel = -1;
}

PENJIN_ERRORS Sound::loadSound(CRstring soundName)
{
	if(channel != -1)
		channel = -1;
	freeAll();
	sound = Mix_LoadWAV(soundName.c_str());										// load sound.wav from sdcard

	if(sound)
		return PENJIN_OK;
	return PENJIN_FILE_NOT_FOUND;
}

bool Sound::isPaused()const
{
    if(channel == -1)
        return false;
	else if(Mix_Paused(channel))
		return true;
	return false;
}

bool Sound::isPlaying()const
{
    if(channel == -1)
        return false;
	else if(Mix_Playing(channel))
		return true;
	return false;
}

void Sound::play()
{
	if(isPaused())
		Mix_Resume(channel);
	else if(channel == -1 || !isPlaying())
		channel = Mix_PlayChannel(channel, sound, loops);
}

void Sound::pause()
{
	if(isPlaying())
		Mix_Pause(channel);
}

void Sound::playPause()
{
    if(isPaused())
        play();
    else if(isPlaying())
        pause();
}

void Sound::stop()
{
    //  Don't stop all channels!
    if(channel != -1)
        Mix_HaltChannel(channel);
}

void Sound::stopAll()
{
    Mix_HaltChannel(-1);
}
