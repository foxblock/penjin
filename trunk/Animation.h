#ifndef ANIMATION_H
#define ANIMATION_H

#include "Image.h"
#include "Timer.h"


class Animation
{
    public:
        Animation();

        void update();
        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);
            void render(){render(screen);}
        #else
            void render();
        #endif
        PENJIN_ERRORS loadFrame(CRstring fileName);     // adds a frame of animation for this sprite
        PENJIN_ERRORS loadFrames(CRstring fileName,CRuint xTiles,CRuint yTiles); // loads a spritesheet for animations
        void setAlpha(const uchar& alpha){image.setAlpha(alpha);}
        PENJIN_ERRORS setTransparentColour(const Colour& c){return image.setTransparentColour(c);}
        PENJIN_ERRORS setTransparentColour(const PENJIN_COLOURS& c){return setTransparentColour(Colour(c));}
        PENJIN_ERRORS setTransparentColour(const Vector2di& v);
        void disableTransparentColour(){image.disableTransparentColour();}
        uchar getAlpha(){return image.getAlpha();}

        void setFrameRate(const TimerScalers& fps){animationTimer.setMode(fps);}
        //  If numLoops is set to minus 1 then this is the same as inf looping.
        void setLooping(CRint numLoops){this->numLoops = firstLoops = numLoops;}
        void setLooping(CRbool shouldLoop)
        {
            if(shouldLoop)
                numLoops = -1;
            else
                numLoops = 0;
        }
        //  Overide the start frame
        void setCurrentFrame(CRuint frame){currentFrame = frame;}
        uint getCurrentFrame()const{return currentFrame;}
        bool hasFinished()const{return((size_t)currentFrame >= image.size()-1 && numLoops == 0);}
        void rewind()
        {
            currentFrame = 0;
            numLoops = firstLoops;
        }
        void setReversePlay(CRbool reverse){playReversed = reverse;}
        #ifndef PENJIN_3D
            void setPosition(const Vector2di& pos){position = pos;}
        #else
            void setPosition(const Vector3df& pos){position = pos;}
        #endif
    private:
        Timer animationTimer;
        Image image;

        #ifndef PENJIN_3D
            Vector2di position;
        #else
            Vector3df position;
        #endif
        #ifdef PENJIN_SDL
            SDL_Surface* screen;
        #endif

        int numLoops;
        int firstLoops;         //  Numloops is stored in case of rewind.
        uint currentFrame;
        bool playReversed;
        bool reachedEnd;        //  Used in conjunction with playReversed.
                            //  Keeps track of which end of the animation we're at.
        bool firstRender;
};
#endif	//	ANIMATION_H
