#ifndef ANIMATIONSTRINGMENUITEM_H_INCLUDED
#define ANIMATIONSTRINGMENUITEM_H_INCLUDED

#include "AnimationMenuItem.h"
#include "StringMenuItem.h"

class AnimationStringMenuItem : public MenuItem
{
    public:
        AnimationStringMenuItem(){init();}
        virtual ~AnimationStringMenuItem();

        virtual void update();
        virtual Vector2di getDimensions();

        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
            virtual void setPosition(const Vector2df& pos);
            void setUseHardware(CRbool use);
        #else
            virtual void render();
            #ifdef PENJIN_3D
                virtual void setPosition(const Vector3df& pos);
            #else
                virtual void setPosition(const Vector2df& pos);
            #endif
        #endif

        /// Animation specific functions
        PENJIN_ERRORS loadFrame(CRstring fileName){return anim.loadFrame(fileName);}
        PENJIN_ERRORS loadFrames(CRstring tileSheet,CRuint xTiles,CRuint yTiles){return anim.loadFrames(tileSheet, xTiles, yTiles);}
        PENJIN_ERRORS loadSelectionFrame(CRstring fileName);
        PENJIN_ERRORS loadSelectionFrames(CRstring tileSheet,CRuint xTiles,CRuint yTiles);
        void setFrameRate(const TimerScalers& fps){anim.setFrameRate(fps);}
        void setLooping(CRint numLoops){anim.setLooping(numLoops);}
        void setLooping(CRbool shouldLoop){anim.setLooping(shouldLoop);}
        void setReversePlay(CRbool reverse){anim.setReversePlay(reverse);}
        void setPulsePlay(CRbool pulse){anim.setPulsePlay(pulse);}

        /// Set text properties - inherited from the text handler passed in
        void setTextHandler(Text* pointer){text.setTextHandler(pointer);}
        void setMenuItemText(CRstring txt){text.setMenuItemText(txt);}
        void setSelectionIndicator(CRchar c){text.setSelectionIndicator(c);}
        void setTextSelectionColour(const Colour& colour){text.setTextSelectionColour(colour);}
        void centreText(CRint corr);

    protected:
        virtual void init();

    private:
        AnimationMenuItem anim;
        StringMenuItem text;
};
#endif // ANIMATIONSTRINGMENUITEM_H_INCLUDED
