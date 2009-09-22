#ifndef INC_AUDIO_H
#define INC_AUDIO_H

#include <AL/al.h>
#include <AL/alut.h>
#include <vorbis/vorbisfile.h>

#include <vector>

class Audio
{
	struct Stream
	{
		FILE*           oggFile;
        OggVorbis_File  oggStream;
        vorbis_info*    vorbisInfo;
        vorbis_comment* vorbisComment;

        ALuint buffers[2];
        ALuint source;
        ALenum format;
	};

	struct Sound
	{
		ALuint sourceID;				// The OpenAL sound source
		ALuint bufferID;				// The OpenAL sound buffer ID
		ALenum format;					// The sound data format
		ALsizei freq;					// The frequency of the sound data
		std::vector<char> bufferData;	// The sound buffer data from file
	};

	public : Audio(int argc, char** argv);
	Audio();
	public : ~Audio();

	// Stream
	public : void loadStream(const char *filename);
	public : void playStream(int id);
	public : void stopStream(int id);

	// Sound
	public : void loadSound(const char *filename);
	public : void playSound(int id);

	// Update
	public : void update();

	private :

		const static int BUFFER_SIZE = 32768;

		std::vector<Stream*> stream;
		std::vector<Sound*>  sound;

	private : void updateStream(int id);
	private : void emptyQueue(int id);
	private : void doStream(ALuint buffer, int id);
	private : void loadOGG(const char *fileName, std::vector<char> &buffer, ALenum &format, ALsizei &freq);
};

#endif
