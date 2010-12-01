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
