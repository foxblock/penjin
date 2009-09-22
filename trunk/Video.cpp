#include "Video.h"
/*
Video::Video(string filename, bool loop)
{
	// File opening =========================

	AVIFileInit();

	//Open avi file
	if(AVIFileOpen(&aviFile, filename, OF_READ, NULL))
		std::cout << "ERROR: Avi file " << filename << " failed to load\n";

	//Get avi info
	if(AVIFileInfo(aviFile, &aviInfo, sizeof(aviInfo)))
		std::cout << "ERROR: Avi file info failed to load\n";

	// Video setup =========================

	//Get video stream
	if(AVIFileGetStream(aviFile, &videoStream, streamtypeVIDEO, 0))
		std::cout << "ERROR: Avi video stream failed to load\n";

	//Get video stream info
	if(AVIStreamInfo(videoStream, &videoInfo, sizeof(videoInfo)))
		std::cout << "ERROR: Avi video info failed to load\n";

	//Get video dimensions
	videoWidth  = videoInfo.rcFrame.right  - videoInfo.rcFrame.left;
	videoHeight = videoInfo.rcFrame.bottom - videoInfo.rcFrame.top;

	//Get the last frame in the video and the number of milliseconds per frame in the video
	videoLastFrame = AVIStreamLength(videoStream);
	videoFrameTime = AVIStreamSampleToTime(videoStream, videoLastFrame) / videoLastFrame;

	//Setup video format
	videoFormat.biSize			= sizeof (BITMAPINFOHEADER);
	videoFormat.biPlanes		= 1;
	videoFormat.biBitCount		= 24;
	videoFormat.biWidth			= 256;
	videoFormat.biHeight		= 256;
	videoFormat.biCompression	= BI_RGB;

	//Create video dib and device context
	videoDib = DrawDibOpen();
	videoDeviceContext = CreateCompatibleDC(0);
	videoBitmap = CreateDIBSection(videoDeviceContext, (BITMAPINFO*)(&videoFormat), DIB_RGB_COLORS, (void**)(&videoData), NULL, NULL);
	SelectObject(videoDeviceContext, videoBitmap);

	//Create video frame object
	videoFrameObject = AVIStreamGetFrameOpen(videoStream, PBITMAPINFOHEADER(AVIGETFRAMEF_BESTDISPLAYFMT));
	if(videoFrameObject == NULL)
		std::cout << "ERROR: Video frame failed to load\n";

	//Create video texture
	//glGenTextures( 1, &texID );
	//glBindTexture( GL_TEXTURE_2D, texID );
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, videoData);

	//Setup frame timers
	videoFrame = 0;
	videoFrameTimer = 0;

	// Audio setup =========================

	//Get audio stream
//	if(AVIFileGetStream(aviFile, &audioStream, streamtypeAUDIO, 0))
//		std::cout << "ERROR: Avi audio stream failed to load\n";
//
	//Get audio stream info
//	if(AVIStreamInfo(audioStream, &audioInfo, sizeof(audioInfo)))
//		std::cout << "ERROR: Avi audio info failed to load\n";

	counter = 0;
	lastCounter = SDL_GetTicks();

	this->loop = loop;
	dead = false;
}

Video::~Video()
{
	DeleteObject(videoBitmap);
	DrawDibClose(videoDib);
	AVIStreamGetFrameClose(videoFrameObject);
	AVIStreamRelease(videoStream);
	//AVIStreamRelease(audioStream);
	AVIFileRelease(aviFile);

	AVIFileExit();
}

void Video::setTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);

	counter = SDL_GetTicks();
	long timer = counter - lastCounter;

	//Calculate frame
	videoFrameTimer += timer;
	videoFrame = videoFrameTimer/videoFrameTime;
	if (videoFrame >= videoLastFrame)
	{
		videoFrame=0;
		videoFrameTimer=0;
		if(!loop)
			dead = true;
	}

	videoBitmapInfo = (LPBITMAPINFOHEADER)AVIStreamGetFrame(videoFrameObject, videoFrame);
	videoTexData = (char *)videoBitmapInfo+videoBitmapInfo->biSize+videoBitmapInfo->biClrUsed * sizeof(RGBQUAD);

	DrawDibDraw(videoDib, videoDeviceContext, 0, 0, 256, 256, videoBitmapInfo, videoTexData, 0, 0, videoWidth, videoHeight, 0);

	byteFlip(videoData);

	//glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, videoData);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, videoData);

	lastCounter = counter;
}

bool Video::checkDead()
{
	return dead;
}

void Video::byteFlip(void* buffer)
{
	void* b = buffer;					// Pointer To The Buffer
	__asm								// Assembler Code To Follow
	{
		mov ecx, 256*256				// Set Up A Counter (Dimensions Of Memory Block)
		mov ebx, b						// Points ebx To Our Data (b)
		label:							// Label Used For Looping
			mov al,[ebx+0]				// Loads Value At ebx Into al
			mov ah,[ebx+2]				// Loads Value At ebx+2 Into ah
			mov [ebx+2],al				// Stores Value In al At ebx+2
			mov [ebx+0],ah				// Stores Value In ah At ebx

			add ebx,3					// Moves Through The Data By 3 Bytes
			dec ecx						// Decreases Our Loop Counter
			jnz label					// If Not Zero Jump Back To Label
	}
}
*/
