#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Image.h"
#include "Timer.h"

class AnimatedSprite
{
    public:
        AnimatedSprite();
        #ifndef PENJIN_SDL
            #ifdef PENJIN3D
                AnimatedSprite(CRfloat x,CRfloat y,CRfloat z);
            #endif
            AnimatedSprite(CRfloat x,CRfloat y);
        #else
            AnimatedSprite(CRint x,CRint y);
        #endif

        PENJIN_ERRORS loadFrame(SDL_Surface* s);
        PENJIN_ERRORS loadFrame(CRstring fileName);     // adds a frame of animation for this sprite
        PENJIN_ERRORS loadFrames(CRstring fileName,CRuint xTiles,CRuint yTiles); // loads a spritesheet for animations
        PENJIN_ERRORS loadFrames(SDL_Surface* s,CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint numTiles); // loads a spritesheet from a shared image
        void setAlpha(const uchar& alpha){image.setAlpha(alpha);}
        PENJIN_ERRORS setTransparentColour(const Colour& c){return image.setTransparentColour(c);}
        PENJIN_ERRORS setTransparentColour(const Vector2di& v);
        PENJIN_ERRORS setTransparentColour(const PENJIN_COLOURS& c){return setTransparentColour(Colour(c));}
        void disableTransparentColour(){image.disableTransparentColour();}
        uchar getAlpha()const{return image.getAlpha();}

        void setPosition(const Vector2di& pos){position.x = pos.x;position.y=pos.y;}
        void setPosition(const Vector2df& pos){position.x=pos.x;position.y=pos.y;}
        #ifndef PENJIN_FIXED
            void setPosition(const Vector2dx& pos){setPosition(pos.x,pos.y);}
        #endif
        void setPosition(CRFixed x, CRFixed y){position.x = fixedpoint::fix2float(x);position.y = fixedpoint::fix2float(y);}
        void setPosition(CRint x,CRint y){setPosition(Vector2di(x,y));}
        float getX()const{return position.x;}
        float getY()const{return position.y;}
        #ifndef PENJIN3D
            Vector2df getPosition()const{return position;}
            void setX(CRint x){position.x = x;}
            void setY(CRint y){position.y = y;}
        #endif
        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);         // Draws the image onto the scre
            void render(){render(screen);}
        #else
            void render();
            void setX(CRfloat x){position.x = x;}
            void setY(CRfloat y){position.y = y;}
            #ifdef PENJIN3D
                Vector3df getPosition()const{return position;}
                void setPosition(const Vector3df& pos){position = pos;}
                void setZ(CRfloat z){position.z = z;}
                float getZ()const{return position.z;}
            #endif
        #endif
        void update();
       // bool hasCollided(AnimatedSprite &spr);		//	Has this sprite collided with the passed in sprite?

        uint getWidth()const{return image.getWidth();}
        uint getHeight()const{return image.getHeight();}
        void setFrameRate(const TimerScalers& fps){animationTimer.setMode(fps);}
        void setTimerScaler(CRfloat cusScaler){animationTimer.setScaler(cusScaler);}//Set a custom timer update scaler.
        void setLooping(CRint numLoops){this->numLoops = firstLoops = numLoops;}
        void setLooping(CRbool shouldLoop)
        {
            if(shouldLoop)
                numLoops = -1;
            else
                numLoops = 0;
        }
        void clearFrames(){image.clear();}
        #ifndef PENJIN3D
            void setScale(CRfloat scale){image.setScale(scale);}
            void setScaleX(CRfloat scaleX){image.setScaleX(scaleX);}
            void setScaleY(CRfloat scaleY){image.setScaleY(scaleY);}
            void setRotation(CRfloat angle){image.setRotation(angle);}
        #endif
        #ifdef PENJIN_SDL
            void setUseHardware(CRbool useHW){image.setUseHardware(useHW);}
        #else
            #ifdef PENJIN3D
                void setScale(const Vector3df& scaleVec){image.setScale(scaleVec);}
                void setRotation(const Vector3df& rotationVec){image.setRotation(rotationVec);}
            #endif
        #endif

        uint getCurrentFrame()const{return currentFrame;}
        bool hasFinished()const{return((size_t)currentFrame >= image.size()-1 && numLoops == 0);}
        bool hasReachedEnd() {return reachedEnd;}
        void resetReachedEnd() {reachedEnd = false;}
        void setReversePlay(CRbool reverse){playReversed = reverse;}
        void rewind(){currentFrame = 0;numLoops = firstLoops;}
        void setCurrentFrame(CRint framenumber){currentFrame = framenumber;}
    private:
        Image image;
        Timer animationTimer;
        int numLoops;
        int firstLoops;
        bool playReversed;
        bool reachedEnd;
        uint currentFrame;
        #ifdef PENJIN3D
            Vector3df position;
        #else
            Vector2df position;
        #endif
        #ifdef PENJIN_SDL
            SDL_Surface* screen;
        #endif
};
#endif	//	ANIMATEDSPRITE_H
