#ifndef ANIMATION_H
#define ANIMATION_H

#include "AnimatedSprite.h"

class Animation : public AnimatedSprite // same as AnimatedSprite, but without auto-keying
{
    public:
        virtual PENJIN_ERRORS loadFrame(CRstring fileName);     // adds a frame of animation for this sprite
        virtual PENJIN_ERRORS loadFrames(CRstring fileName,CRuint xTiles,CRuint yTiles); // loads a spritesheet for animations
};
#endif	//	ANIMATION_H
