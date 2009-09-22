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
