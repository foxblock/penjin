#include "StateAnimation.h"
#include "Animation.h"
#include "AnimatedSprite.h"
StateAnimation::StateAnimation()
{
    //ctor
    anim = NULL;
    looping = true;
    paused = false;
    playMode = pmNormal;
    animMode = ANIM_TILE;
    fpsMode = SECONDS;
}

StateAnimation::~StateAnimation()
{
    //dtor
    clear();
}

void StateAnimation::clear()
{
    delete anim;
    anim = NULL;
}

void StateAnimation::init()
{
    GFX::setClearColour(BLACK);
    text.loadFont("font/unispace.ttf",15);
    text.setPosition(GFX::getXResolution()-400, 50);
    text.setBoundaries(Vector2di(0,0),Vector2di(GFX::getXResolution(),GFX::getYResolution()));
    text.setRelativity(true);
    changeAnimMode();
    setFPS();
}

void StateAnimation::render()
{
    GFX::clearScreen();
    text.setPosition(GFX::getXResolution()-400, 50);
    if(anim)
    {
        anim->render();
        text.print("Mode (A): ");
        switch (animMode)
        {
            case ANIM_TILE:
                text.print("Animation, TILESHEET\n");
                break;
            case ANIM_FRAMES:
                text.print("Animation, FRAMES\n");
                break;
            case SPR_TILE:
                text.print("AnimatedSprite, TILESHEET\n");
                break;
            case SPR_FRAMES:
                text.print("AnimatedSprite, FRAMES\n");
                break;
        }
        text.print("Frame: ");
        text.print((int)anim->getCurrentFrame());
        text.print("\n");
        if(anim->hasFinished())
        {
            text.print("Finished\n");
        }
    }

    text.print("Paused (X): ");
    if (paused)
        text.print("true\n");
    else
        text.print("false\n");

    text.print("Looping (L): ");
    if(looping)
        text.print("true\n");
    else
        text.print("false\n");

    text.print("Play mode (R): ");
    switch (playMode)
    {
        case pmNormal:
            text.print("Normal\n");
            break;
        case pmReverse:
            text.print("Reverse\n");
            break;
        case pmPulse:
            text.print("Pulsing\n");
            break;
    }

    text.print("FPS (B): ");
    if(fpsMode == FIFTEEN_FRAMES)
        text.print("FIFTEEN_FRAMES");
    else if(fpsMode == THIRTY_FRAMES)
        text.print("THIRTY_FRAMES");
    else if(fpsMode == FIFTY_FRAMES)
        text.print("FIFTY_FRAMES");
    else if(fpsMode == SIXTY_FRAMES)
        text.print("SIXTY_FRAMES");
    else if(fpsMode == MILLI_SECONDS)
        text.print("MILLI_SECONDS");
    else if(fpsMode == CENTI_SECONDS)
        text.print("CENTI_SECONDS");
    else if(fpsMode == DECI_SECONDS)
        text.print("DECI_SECONDS");
    else if(fpsMode == SECONDS)
        text.print("SECONDS");
    else if(fpsMode == MINUTES)
        text.print("MINUTES");
    text.print("\n\n");

    text.print("LEFT to rewind");
}

void StateAnimation::unlimitedUpdate()
{
    if(anim && not paused)
        anim->update();
}

void StateAnimation::userInput()
{
    /*
    A button toggles through the different animation objects and frame load methods
    L button toggles looping
    R button cycles through play modes
    B cycles fps scalers in timer.
    LEFT rewinds the animation.
    X toggles pause
    */
    input->update();
    #ifdef PLATFORM_PC
        if(input->isQuit())
            nullifyState();
    #endif
    if(input->isStart())
        setNextState(STATE_TITLE);
    if(input->isA())
    {
        ++animMode;
        changeAnimMode();
    }
    if(input->isB())
    {
        cycleTimerMode();
    }
    if(input->isLeft())
    {
        rewind();
    }
    if(input->isL())
    {
        looping = !looping;
        setLooping();
    }
    if(input->isR())
    {
        cyclePlayMode();
    }
    if (input->isX())
        togglePause();
    input->resetKeys();
}

void StateAnimation::changeAnimMode()
{
    string dir = "images/";
    string ext = ".png";
    if(animMode < 0)
        animMode = SPR_FRAMES;
    else if(animMode > SPR_FRAMES)
        animMode = ANIM_TILE;

    // delete old sprite
    clear();

    if(animMode == ANIM_TILE) // Animation (no auto-keying) loaded from a sprite-sheet
    {
        anim = new Animation;
        Animation* temp = (Animation*)anim;
        temp->loadFrames(dir+"frames"+ext,1,6);
        temp->setFrameRate(SECONDS);
    }
    else if(animMode == ANIM_FRAMES) // Animation loaded from individual frames
    {
        anim = new Animation;
        Animation* temp = (Animation*)anim;
        temp->loadFrame(dir+"frames/1"+ext);
        temp->loadFrame(dir+"frames/2"+ext);
        temp->loadFrame(dir+"frames/3"+ext);
        temp->loadFrame(dir+"frames/4"+ext);
        temp->loadFrame(dir+"frames/5"+ext);
        temp->loadFrame(dir+"frames/6"+ext);
        temp->setFrameRate(SECONDS);
    }
    else if(animMode == SPR_TILE) // AnimatedSprite (with auto-keying) loaded from sprite-sheet
    {
        anim = new AnimatedSprite;
        anim->loadFrames(dir+"frames"+ext,1,6);
        anim->setFrameRate(SECONDS);
    }
    else if(animMode == SPR_FRAMES) // AnimatedSprite loaded from individual frames
    {
        anim = new AnimatedSprite;
        anim->loadFrame(dir+"frames/1"+ext);
        anim->loadFrame(dir+"frames/2"+ext);
        anim->loadFrame(dir+"frames/3"+ext);
        anim->loadFrame(dir+"frames/4"+ext);
        anim->loadFrame(dir+"frames/5"+ext);
        anim->loadFrame(dir+"frames/6"+ext);
        anim->setFrameRate(SECONDS);
    }
    anim->setPosition(50,200);
    setLooping();
    anim->setPlayMode((PlayMode)playMode);
}

void StateAnimation::setLooping()
{
    if(anim)
        anim->setLooping(looping);
}

void StateAnimation::cyclePlayMode()
{
    if(anim)
    {
        switch(anim->getPlayMode())
        {
            case pmNormal:
                anim->setPlayMode(pmReverse);
                break;
            case pmReverse:
                anim->setPlayMode(pmPulse);
                break;
            case pmPulse:
                anim->setPlayMode(pmNormal);
                break;
        }
        playMode = anim->getPlayMode();
    }
}

void StateAnimation::togglePause()
{
    paused = !paused;
}

void StateAnimation::setFPS()
{
    if(anim)
        anim->setFrameRate((TimerScalers)fpsMode);
}

void StateAnimation::rewind()
{
    if(anim)
        anim->rewind();
}

void StateAnimation::cycleTimerMode()
{
    /*
    MILLI_SECONDS=1000,
    CENTI_SECONDS=100,
    SIXTY_FRAMES=60,
    FIFTY_FRAMES=50,
    THIRTY_FRAMES=30,
    FIFTEEN_FRAMES=15,
    DECI_SECONDS=10,
    SECONDS=1,
    MINUTES,
    HOURS,
    CUSTOM
    */
        if(fpsMode == MILLI_SECONDS)
            fpsMode = CENTI_SECONDS;
        else if(fpsMode == CENTI_SECONDS)
            fpsMode = SIXTY_FRAMES;
        else if(fpsMode == SIXTY_FRAMES)
            fpsMode = FIFTY_FRAMES;
        else if(fpsMode == FIFTY_FRAMES)
            fpsMode = THIRTY_FRAMES;
        else if(fpsMode == THIRTY_FRAMES)
            fpsMode = FIFTEEN_FRAMES;
        else if(fpsMode == FIFTEEN_FRAMES)
            fpsMode = DECI_SECONDS;
        else if(fpsMode == DECI_SECONDS)
            fpsMode = SECONDS;
        else if(fpsMode == SECONDS)
            fpsMode = MINUTES;
        else if(fpsMode == MINUTES)
            fpsMode = MILLI_SECONDS;
        setFPS();
}
