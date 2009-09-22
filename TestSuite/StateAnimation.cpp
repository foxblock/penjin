#include "StateAnimation.h"

StateAnimation::StateAnimation()
{
    //ctor
    anim =NULL;
    animS = NULL;
    looping = true;
    paused = true;
    reverse = false;
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
    if(anim)
        delete anim;
    if(animS)
        delete animS;

    anim = NULL;
    animS = NULL;
}

void StateAnimation::init()
{
    GFX::setClearColour(BLACK);
    text.loadFont("font/unispace.ttf",15);
    text.setPosition(40, getStateYResolution()-80);
    text.setBoundaries(Vector2di(0,0),Vector2di(getStateXResolution(),getStateYResolution()));
    text.setRelativity(true);
    changeAnimMode();
    setFPS();
    setPause();
}

void StateAnimation::render()
{
    GFX::clearScreen();
    text.setPosition(40, getStateYResolution()-80);
    if(anim)
    {
        anim->render();
        text.print("Animation: ");
        if(animMode == ANIM_TILE)
            text.print("TILES ");
        else
            text.print("FRAMES ");
        text.print("Frame: ");text.print((int)anim->getCurrentFrame());
        if(anim->hasFinished())
        {
            text.print("  Finished!");
        }
    }
    else if(animS)
    {
        animS->render();
        text.print("AnimatedSprite: ");
        if(animMode == SPR_TILE)
            text.print("TILES ");
        else
            text.print("FRAMES ");
        text.print("Frame: ");text.print((int)animS->getCurrentFrame());
        if(animS->hasFinished())
        {
            text.print("  Finished!");
        }
    }
    if(looping)
        text.print("   Looping     ");
    else
        text.print("   No Looping  ");
    if(reverse)
        text.print("ReversePlay    ");
    else
        text.print("No ReversePlay ");

    text.setPosition(40, getStateYResolution()-120);
    if(fpsMode == FIFTEEN_FRAMES)
        text.print("FIFTEEN_FRAMES");
    else if(fpsMode == THIRTY_FRAMES)
        text.print("THIRTY_FRAMES");
    else if(fpsMode == FIFTY_FRAMES)
        text.print("FIFTY_FRAMES");
    else if(fpsMode == SIXTY_FRAMES)
        text.print("SIXTY_FRAMES");
    else if(fpsMode == NANO_SECONDS)
        text.print("NANO_SECONDS");
    else if(fpsMode == MICRO_SECONDS)
        text.print("MICRO_SECONDS");
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
}

void StateAnimation::update()
{
    if(anim)
        anim->update();
    else if(animS)
        animS->update();
}

void StateAnimation::unlimitedUpdate()
{
}

void StateAnimation::userInput()
{
    /*
    A button toggles through the different animation objects and frame load methods
    L button toggles looping
    R button toggles reverse play
    B cycles fps scalers in timer.
    LEFT rewinds the animation.
    */
    input->update();
    #ifdef PLATFORM_PC
        if(input->isQuit())
            nullifyState();
    #endif
    if(input->isA())
    {
        ++animMode;
        changeAnimMode();
    }
    if(input->isB())
    {
        ++fpsMode;
        setFPS();
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
        reverse = !reverse;
        setReverse();
    }
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
    clear();
    if(animMode == ANIM_TILE)
    {
        anim = new Animation;
        anim->loadFrames(dir+"sheet_3x1_tiles"+ext,3,1);
        anim->setFrameRate(SECONDS);
    }
    else if(animMode == ANIM_FRAMES)
    {
        anim = new Animation;
        anim->loadFrame(dir+"frames/01"+ext);
        anim->loadFrame(dir+"frames/02"+ext);
        anim->loadFrame(dir+"frames/03"+ext);
        anim->setFrameRate(SECONDS);
    }
    else if(animMode == SPR_TILE)
    {
        animS = new AnimatedSprite;
        animS->loadFrames(dir+"sheet_3x1_tiles"+ext,3,1);
        animS->setFrameRate(SECONDS);
    }
    else if(animMode == SPR_FRAMES)
    {
        animS = new AnimatedSprite;
        animS->loadFrame(dir+"frames/01"+ext);
        animS->loadFrame(dir+"frames/02"+ext);
        animS->loadFrame(dir+"frames/03"+ext);
        animS->setFrameRate(SECONDS);
    }
    setLooping();
    setReverse();
}

void StateAnimation::setLooping()
{
    if(anim)
        anim->setLooping(looping);
    else if(animS)
        animS->setLooping(looping);
}

void StateAnimation::setReverse()
{
    if(anim)
        anim->setReversePlay(reverse);
    else if(animS)
        animS->setReversePlay(reverse);
}

void StateAnimation::setPause()
{
    paused = !paused;
}

void StateAnimation::setFPS()
{
    if(fpsMode < FIFTEEN_FRAMES)
        fpsMode = MINUTES;
    else if(fpsMode > MINUTES)
        fpsMode = FIFTEEN_FRAMES;
    if(anim)
        anim->setFrameRate((TimerScalers)fpsMode);
    else if(animS)
        animS->setFrameRate((TimerScalers)fpsMode);
}

void StateAnimation::rewind()
{
    if(anim)
        anim->rewind();
    else if(animS)
        animS->rewind();
}

