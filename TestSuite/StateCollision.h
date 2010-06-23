#ifndef STATECOLLISION_H
#define STATECOLLISION_H

#include "PenjinStates.h"

#include <time.h>
#include "GFX.h"
#include "Text.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "CollisionRegion.h"
#include "StringUtility.h"
#include "Line.h"

using namespace StringUtility;

#define BULLET_SPEED 4
#define CRITTER_SPEED 2

class StateCollision : public BaseState
{
    public:
        StateCollision();
        virtual ~StateCollision();

        virtual void init();
        virtual void render();
        virtual void userInput();
        virtual void update();

    private:
        Text text;
        Sprite bg;
        Sprite bullet;
        AnimatedSprite critter;
        CollisionRegion bgCol;
        CollisionRegion critterCol;
        CollisionRegion bulletCol;
        Line cursor;

        enum optionFlags
        {
            useCollisionImages=0,
            useRegions,
            fullShapeCheck,
            movingBullet,
            renderCollision
        };
        bool options[5];

        bool isCollision;
        string whoCollision;
        string dirCollision;
        int updateTime;
};

#endif // STATECOLLISION_H
