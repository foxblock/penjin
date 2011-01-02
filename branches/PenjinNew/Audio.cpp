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
#include "Audio.h"

Audio::Audio(int argc, char** argv)
{
	alutInit(&argc, argv);

	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
}

Audio::Audio()
{
    int argc = 0;
    char** argv = NULL;
    	alutInit(&argc, argv);

	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
}

Audio::~Audio()
{
	//Clear streams
	for(unsigned int i=0 ; i<stream.size() ; i++)
	{
		alSourceStop(stream[i]->source);

		emptyQueue(i);

		alDeleteSources(1, &(stream[i]->source));
		alDeleteBuffers(1, stream[i]->buffers);

		ov_clear(&(stream[i]->oggStream));

		delete stream[i];
	}
	stream.clear();

	//Clear sounds
	for(unsigned int i=0 ; i<sound.size() ; i++)
	{
		alDeleteBuffers(1, &(sound[i]->bufferID));
		alDeleteSources(1, &(sound[i]->sourceID));
		delete sound[i];
	}
	sound.clear();

	alutExit();
}

void Audio::loadStream(const char *filename)
{
	stream.push_back(new Stream);

    stream.back()->oggFile = fopen(filename, "rb");

	ov_open_callbacks(stream.back()->oggFile, &(stream.back()->oggStream), NULL, 0, OV_CALLBACKS_DEFAULT);

    stream.back()->vorbisInfo = ov_info(&(stream.back()->oggStream), -1);
    stream.back()->vorbisComment = ov_comment(&(stream.back()->oggStream), -1);

    if(stream.back()->vorbisInfo->channels == 1)
        stream.back()->format = AL_FORMAT_MONO16;
    else
        stream.back()->format = AL_FORMAT_STEREO16;

    alGenBuffers(2, stream.back()->buffers);
    alGenSources(1, &(stream.back()->source));

    alSource3f(stream.back()->source, AL_POSITION, 0.0, 0.0, 0.0);
}

void Audio::playStream(int id)
{
    doStream(stream[id]->buffers[0], id);

    doStream(stream[id]->buffers[1], id);

    alSourceQueueBuffers(stream[id]->source, 2, stream[id]->buffers);
    alSourcePlay(stream[id]->source);
}

void Audio::stopStream(int id)
{
	alSourceStop(stream[id]->source);
}

void Audio::loadSound(const char *filename)
{
	sound.push_back(new Sound);

	alGenSources(1, &(sound.back()->sourceID));
	alGenBuffers(1, &(sound.back()->bufferID));

	alSource3f(sound.back()->sourceID, AL_POSITION, 0.0f, 0.0f, 0.0f);

	// Load ogg
	loadOGG(filename, sound.back()->bufferData, sound.back()->format, sound.back()->freq);

	// Upload sound data to buffer
	alBufferData(sound.back()->bufferID, sound.back()->format, &(sound.back()->bufferData[0]), static_cast<ALsizei> (sound.back()->bufferData.size()), sound.back()->freq);

	// Attach sound buffer to source
	alSourcei(sound.back()->sourceID, AL_BUFFER, sound.back()->bufferID);
}

void Audio::playSound(int id)
{
	alSourcePlay(sound[id]->sourceID);
}


void Audio::update()
{
	for(unsigned int i=0 ; i<stream.size() ; i++)
		updateStream(i);
}

void Audio::updateStream(int id)
{
    int processed;
    bool active = true;

    alGetSourcei(stream[id]->source, AL_BUFFERS_PROCESSED, &processed);

    while(processed--)
    {
        ALuint buffer;

        alSourceUnqueueBuffers(stream[id]->source, 1, &buffer);

        doStream(buffer, id);

        alSourceQueueBuffers(stream[id]->source, 1, &buffer);
    }
}

void Audio::emptyQueue(int id)
{
    int queued;

    alGetSourcei(stream[id]->source, AL_BUFFERS_QUEUED, &queued);

    while(queued--)
    {
        ALuint buffer;
        alSourceUnqueueBuffers(stream[id]->source, 1, &buffer);
    }
}

void Audio::doStream(ALuint buffer, int id)
{
    char pcm[BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;

    while(size < BUFFER_SIZE)
    {
        result = ov_read(&(stream[id]->oggStream), pcm + size, BUFFER_SIZE - size, 0, 2, 1, &section);
		size += result;
    }

    alBufferData(buffer, stream[id]->format, pcm, size, stream[id]->vorbisInfo->rate);
}

void Audio::loadOGG(const char *fileName, std::vector<char> &buffer, ALenum &format, ALsizei &freq)
{
	int endian = 0;             // 0 for Little-Endian, 1 for Big-Endian
	int bitStream;
	long bytes;
	char array[BUFFER_SIZE];    // Local fixed size array
	FILE *f;

	// Open for binary reading
	f = fopen(fileName, "rb");

	vorbis_info *pInfo;
	OggVorbis_File oggFile;

	ov_open_callbacks(f, &oggFile, NULL, 0, OV_CALLBACKS_DEFAULT);

	// Get some information about the OGG file
	pInfo = ov_info(&oggFile, -1);

	// Check the number of channels... always use 16-bit samples
	if (pInfo->channels == 1)
		format = AL_FORMAT_MONO16;
	else
		format = AL_FORMAT_STEREO16;
	// end if

	// The frequency of the sampling rate
	freq = pInfo->rate;

	do {
		// Read up to a buffer's worth of decoded sound data
		bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);
		// Append to end of buffer
		buffer.insert(buffer.end(), array, array + bytes);
	} while (bytes > 0);

	ov_clear(&oggFile);
}
