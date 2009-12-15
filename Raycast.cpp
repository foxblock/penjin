//-----------------------------------------------------------------
// Game File
// C++ Source - Raycast.cpp - version 2008 v2_05
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Raycast.h"

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,2,0,2,0,2,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,2,0,0,0,2,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,2,0,2,0,2,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// Raycast methods
//-----------------------------------------------------------------

Raycast::Raycast() : screenX(0), screenY(0), screenWidth(800), screenHeight(480), texSize(64)
{
    LUT::init();
    #ifdef PENJIN_SDL
        screen = SDL_GetVideoSurface();
    #endif
}
Raycast::~Raycast()
{
    LUT::deInit();
}
void Raycast::init(int x, int y, int w, int h)
{
    screenX = x;
    screenY = y;

    screenWidth = w;
    screenHeight = h;
    pixelCache.resize(screenWidth-x,screenHeight-y);

	posX = 22;
	posY = 12;  //x and y start position
	dirX = -1;
	dirY = 0; //initial direction vector
	planeX = 0;
	planeY = 0.74; //the 2d raycaster version of camera plane

    drawSurface.loadBackground("images/DarkTreasure/Surface.png");
    #ifdef PENJIN_SDL
    drawSurface.setUseHardware(true);
    #endif
    drawSurface.setPosition(Vector2di(screenX,screenY));

    time = 0;
    oldTime = 0;

	fps.setPosition(64,64);
    fps.loadFont("font/unispace.ttf",15);

    frameTime = 0;

    distanceColour = Colour(255, 255, 255);
}
#ifdef PENJIN_SDL
void Raycast::render(SDL_Surface* screen)
{
    clearPixels();
    drawSurface.render(screen);
    //buff.update();//Set the buffer to be the same as the

    for(int x = screenX; x < (float) (screenX+screenWidth); ++x)
    {
        //calculate ray position and direction
        float cameraX = 2 * x / (float) (screenX+screenWidth) - 1; //x-coordinate in camera space
        float rayPosX = posX;
        float rayPosY = posY;
        float rayDirX = dirX + planeX * cameraX;
        float rayDirY = dirY + planeY * cameraX;
        //which box of the map we're in
        int mapX = int(rayPosX);
        int mapY = int(rayPosY);

        //length of ray from current position to next x or y-side
        float sideDistX;
        float sideDistY;

        //length of ray from one x or y-side to next x or y-side
        float deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        float deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
        float perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?
        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
        stepX = -1;
        sideDistX = (rayPosX - mapX) * deltaDistX;
        }
        else
        {
        stepX = 1;
        sideDistX = (mapX + 1.0f - rayPosX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
        stepY = -1;
        sideDistY = (rayPosY - mapY) * deltaDistY;
        }
        else
        {
        stepY = 1;
        sideDistY = (mapY + 1.0f - rayPosY) * deltaDistY;
        }
        //perform DDA
        while (hit == 0)
        {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) hit = 1;
        }
        //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
        if (side == 0)
        perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
        else
        perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

        //Calculate height of line to draw on screen
        int lineHeight = abs(int((float) (screenY+screenHeight) / perpWallDist));

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = (-lineHeight / 2 + (float) (screenY * 2 +screenHeight) / 2);
        if(drawStart < screenY) drawStart = screenY;
        int drawEnd = lineHeight / 2 + (float) (screenY * 2 +screenHeight) / 2;
        if(drawEnd >= (float) (screenY+screenHeight)) drawEnd = (float) (screenY+screenHeight);

        //texturing calculations
        int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

        //calculate value of wallX
        float wallX; //where exactly the wall was hit
        if (side == 1) wallX = rayPosX + ((mapY - rayPosY + (1 - stepY) / 2) / rayDirY) * rayDirX;
        else wallX = rayPosY + ((mapX - rayPosX + (1 - stepX) / 2) / rayDirX) * rayDirY;
        wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = int(wallX * float(texSize));
      if(side == 0 && rayDirX > 0) texX = texSize - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texSize - texX - 1;

    for(int y = drawStart; y < drawEnd; y++)
      {
        float d = y * 256 - (screenY * 2 + screenHeight) * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
        float texY = ((d * texSize) / lineHeight) / 256;

        Colour c = textures.getPixel(texNum, texX, texY);

//        c.red = sqrt(c.red * distanceColour.red) * distance;
//        if (c.red < 0) c.red == 0;
//        if (c.red > 255) c.red == 255;
//        c.green = sqrt(c.green * distanceColour.green) * distance;
//        if (c.green < 0) c.green == 0;
//        if (c.green > 255) c.green == 255;
//        c.blue = sqrt(c.blue * distanceColour.blue) * distance;
//        if (c.blue < 0) c.blue == 0;
//        if (c.blue > 255) c.blue == 255;

        if(c.alpha != 0)
        {
            if(side == 1)
                setPixel(Vector2di(x, y), c / 2);
            else
                setPixel(Vector2di(x, y), c);
        }
      }
    }
    renderPixels(screen);
	fps.print(screen,frameTime);
}
#else
void Raycast::render()
{
}
#endif
void Raycast::userInput(SimpleJoy* input)
{
        //speed modifiers
    float moveSpeed = 0.2f; //the constant value is in squares/second
    uchar rotSpeed = 3; //the constant value is in radians/second

    if(input->isUp())
    {
        if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
        if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if(input->isDown())
    {
        if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
        if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }
    //rotate to the right
    if(input->isRight())
    {
      //both camera direction and camera plane must be rotated
        float sinV = LUT::Lsin(-rotSpeed);
        float cosV = LUT::Lcos(-rotSpeed);
        rotate(sinV,cosV);
    }
    //rotate to the left
    if(input->isLeft())
    {
        //both camera direction and camera plane must be rotated
        float sinV = LUT::Lsin(rotSpeed);
        float cosV = LUT::Lcos(rotSpeed);
        rotate(sinV,cosV);
    }
}

void Raycast::clearPixels()
{
    for(int x = pixelCache.size()-1; x>=0;--x)
    {
        for(int y = pixelCache[x].size()-1; y>=0;--y)
        {
           pixelCache[x][y].setColour((uchar)0,0,0,0);
        }
    }
}

void Raycast::setPixel(const Vector2di& v, const Colour& c)
{
    int xsize = pixelCache.size();
    if(v.x >= xsize+screenX)
        return;
    if(v.y >= pixelCache[xsize-1].size()+screenY)
        return;
    pixelCache[v.x-screenX][v.y-screenY]=c;
}

void Raycast::renderPixels(SDL_Surface* screen)
{
    // Run through the horizontal parts of the Pixelcache
    #ifdef PENJIN_SDL
    GFX::lockSurface(screen);
    #endif
    for(int x = pixelCache.size()-1; x>=0;--x)
    {
        int startI=pixelCache[x].size()-1;
        //run through each pixel collumn
        for(int y = pixelCache[x].size()-1; y>=0;--y)
        {
            // if there is a mismatch
            if(pixelCache[x][startI] != pixelCache[x][y])
            {
                //  check how many pixels have been counted
                if(startI-y > 1)
                {
                    // draw a line for these pixels
                    /*
                    line.setColour(pixelCache[x][startI]);
                    line.setStartPosition(Vector2di(x,startI));
                    line.setEndPosition(Vector2di(x,y+1));
                    line.render(screen);*/
                    drawLineV(screen,Vector2di(x,startI),y,pixelCache[x][startI]);
                }
                else
                {
                    /*
                    pix.setColour(pixelCache[x][y+1]);
                    pix.setPosition(Vector2di(x,y+1));
                    pix.render(screen);*/
                    drawPixel(screen,Vector2di(x,y+1),pixelCache[x][y+1]);
                }
                // advance the loop and reset count
                startI = y;
            }
            else if(y == 0)// otherwise we are going to move onto next vertical strip
            {
                if(startI-y > 1)
                {

                    // draw a line for these pixels
                    /*line.setColour(pixelCache[x][startI]);
                    line.setStartPosition(Vector2di(x,startI));
                    line.setEndPosition(Vector2di(x,y));
                    line.render(screen);*/
                    drawLineV(screen,Vector2di(x,startI),y,pixelCache[x][startI]);
                }
                /*else
                {

                    pix.setColour(pixelCache[x][y+1]);
                    pix.setPosition(Vector2di(x,y+1));
                    pix.render(screen);
                }*/
            }
        }
    }
    #ifdef PENJIN_SDL
    GFX::unlockSurface(screen);
    #endif
}

void Raycast::loadTexture(CRstring imageName)
{
    textures.loadImage(imageName);
}
