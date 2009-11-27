//-----------------------------------------------------------------
// Game File
// C++ Header - Raycast.h - version 2008 v2_05
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <cmath>
#include "DoubleVector.h"

#include "Colour.h"
//#include "Line.h"
#include "SimpleJoy.h"
#include "Background.h"
#include "GFX.h"
//#include "Pixel.h"
#include "LUT.h"
#include "Text.h"

//-----------------------------------------------------------------
// Raycast Class
//-----------------------------------------------------------------
class Raycast
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	Raycast();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Raycast();

	//---------------------------
	// General Methods
	//---------------------------

    void init(int x, int y, int w, int h);
    void setTextureSize(int size){texSize = size;}
	#ifdef PENJIN_SDL
	void render(SDL_Surface* screen);
	#else
	void render();
	#endif
	void userInput(SimpleJoy* input);
	void loadTexture(CRstring imageName);

private:
    void rotate(CRfloat sinV,CRfloat cosV)
    {
        float oldDirX = dirX;
        dirX = dirX * cosV - dirY * sinV;
        dirY = oldDirX * sinV + dirY * cosV;
        float oldPlaneX = planeX;
        planeX = planeX * cosV - planeY * sinV;
        planeY = oldPlaneX * sinV + planeY * cosV;
    }
    void clearPixels();
    void setPixel(const Vector2di& v,const Colour& c); // set a pixel to be queued to the screen
    void drawLineV(SDL_Surface* screen, const Vector2di& start, CRuint endX, const Colour& c){
    vlineRGBA(screen,start.x+screenX, start.y+screenY,
endX+screenX, c.red,c.green,c.blue,c.alpha);}
    void drawPixel(SDL_Surface* screen, const Vector2di& p, const Colour& c){pixelRGBA(screen, p.x+screenX, p.y+screenY, c.red,c.green, c.blue, c.alpha);}
    void renderPixels(SDL_Surface* screen);                                //  Render all the pixels

    DoubleVector<Colour> pixelCache;  // stores potential pixels to render

	// -------------------------
	// Datamembers
	// -------------------------

    int screenWidth, screenHeight, screenX, screenY, texSize;

	float posX, posY;
	float dirX, dirY;
	float planeX, planeY;

	Colour distanceColour;
	float distance;

	Image textures;

    Background drawSurface;
	//Pixel pix;
	//Line line;

	Text fps;

	float time;
    float oldTime;
    float frameTime;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Raycast(const Raycast& tRef);
	Raycast& operator=(const Raycast& tRef);
};
