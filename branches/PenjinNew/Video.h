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
#ifndef INC_VIDEO_H
#define INC_VIDEO_H
/*
#include <windows.h>
#include <vfw.h>
#include <iostream>
#include <conio.h>
#include <SDL.h>
#include "SDL_opengl.h"	//OpenGL Utility Toolkit library header file

class Video
{
	public : Video(LPCSTR filename, bool loop);
	public : ~Video();
	public : void setTexture();
	public : bool checkDead();

	private :

		PAVIFILE aviFile;						//The avi file
		AVIFILEINFO aviInfo;					//The avi file info
		PAVISTREAM audioStream, videoStream;	//The audio and video streams
		AVISTREAMINFO audioInfo, videoInfo;		//The audio and video stream info

		int videoWidth, videoHeight;			//Video dimensions
		long videoLastFrame;					//Last frame in the video
		int videoFrameTime;						//Milliseconds per frame

		BITMAPINFOHEADER videoFormat;			//Video format
		HDRAWDIB videoDib;						//Video dib
		HDC videoDeviceContext;					//Video device context
		HBITMAP videoBitmap;					//Video bitmap

		unsigned char* videoData;				//Video image data
		PGETFRAME videoFrameObject;				//Video frame object
		LPBITMAPINFOHEADER videoBitmapInfo;		//Video frame bitmap info

		char* videoTexData;						//Video texture data

		long videoFrame;						//Current video frame index
		long videoFrameTimer;					//Video frame timer

		long counter;
		long lastCounter;

		bool loop;
		bool dead;

	private : void byteFlip(void* buffer);
};
*/

#endif
