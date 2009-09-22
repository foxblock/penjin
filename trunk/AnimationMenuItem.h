#ifndef ANIMATIONMENUITEM_H_INCLUDED
#define ANIMATIONMENUITEM_H_INCLUDED

#include "MenuItem.h"
#include "AnimatedSprite.h"

class AnimationMenuItem : public MenuItem
{
    public:
        AnimationMenuItem(){init();}
        AnimationMenuItem(CRstring tilesheet,CRuint xTiles,CRuint yTiles){init();anim.loadFrames(tilesheet,xTiles,yTiles);}
        AnimationMenuItem(AnimatedSprite* selectedAnim){init();selection = selectedAnim;}

        virtual ~AnimationMenuItem();

        virtual void update();
        virtual  Vector2di getDimensions();

        #ifdef PENJIN_SDL
            void setUseHardware(CRbool use);
            virtual void render(SDL_Surface* screen);
        #else
            virtual void render();
        #endif

        /// Animation specific functions
        PENJIN_ERRORS loadFrame(CRstring fileName);
        PENJIN_ERRORS loadFrames(CRstring tileSheet,CRuint xTiles,CRuint yTiles);
        PENJIN_ERRORS loadSelectionFrame(CRstring fileName);
        PENJIN_ERRORS loadSelectionFrames(CRstring tileSheet,CRuint xTiles,CRuint yTiles);
        void setFrameRate(const TimerScalers& fps){anim.setFrameRate(fps);}
        void setLooping(CRint numLoops){anim.setLooping(numLoops);}
        void setLooping(CRbool shouldLoop){anim.setLooping(shouldLoop);}
        void setReversePlay(CRbool reverse){anim.setReversePlay(reverse);}

    protected:
        virtual void init();

    private:
        AnimatedSprite anim;
        AnimatedSprite* selection;
};

#endif // ANIMATIONMENUITEM_H_INCLUDED
