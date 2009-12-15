#include "ScoreScreen.h"

ScoreScreen::ScoreScreen()
{
    //ctor
	scoreFile = "scores.txt";
	nameEntry = true;
	textStrings[1] = "";
	score = 0;
	currentLetter = 'A';
	#ifdef PENJIN_SDL
        screen = SDL_GetVideoSurface();
    #endif
}

ScoreScreen::ScoreScreen(CRstring scoreFile)
{
    this->scoreFile = scoreFile;
//    firstPass = true;
	nameEntry = true;
	textStrings[1] = "";
	score = 0;
	currentLetter = 'A';
	#ifdef PENJIN_SDL
        screen = SDL_GetVideoSurface();
    #endif
}

void ScoreScreen::init()
{
    //  First load scores
    if(scores.loadScores(scoreFile) != PENJIN_OK)
	{
	    scores.initialiseTables();
        scores.saveScores(scoreFile);
	}
	scores.setBoundaries(bounds);
	// Create a nice starfield effect
	emit.resize(3);
	emit[0].setMax(bounds.w/bounds.h*200);
	emit[0].setBoundaries(bounds);
	emit[0].setPosition(Vector2di(bounds.w*0.5f,bounds.h*0.5f));
	emit[0].setLifeTime(3000);
	emit[0].setMaxVelocity(Vector2df(2.8f,2.8f));
	emit[0].setDeviation(0.01f);
    emit[1].setMax(bounds.w/bounds.h*100);
	emit[1].setBoundaries(bounds);
	emit[1].setPosition(Vector2di(bounds.w*0.5f,bounds.h*0.5f));
	emit[1].setLifeTime(1500);
	emit[1].setMaxVelocity(Vector2df(3.8f,3.8f));
	emit[1].setDeviation(0.05f);
    emit[1].setColour(Colour(YELLOW));
    emit[2].setMax(bounds.w/bounds.h*50);
	emit[2].setBoundaries(bounds);
	emit[2].setPosition(Vector2di(bounds.w*0.5f,bounds.h*0.5f));
	emit[2].setLifeTime(1100);
	emit[2].setMaxVelocity(Vector2df(4.5f,4.5f));
	emit[2].setDeviation(0.05f);
    emit[2].setColour(Colour(128,128,255));

    /// PreUpdate emitters
    for(int i = emit.size()-1;i >=0; --i)
        emit[i].advanceUpdate(120);

    /// setup Text positions
    textStrings[0] = "   ";
    textStrings[2] = "OK?";
    textStrings[3] = "Game Over!";
    #ifdef PENJIN_SDL
        SDL_Surface* scr = SDL_GetVideoSurface();
    #endif
    float t = 0.2f;
    text.setBoundaries(bounds);
    for(int i = 3; i >= 0; --i)
    {
        #ifdef PENJIN_SDL
            text.print(NULL, textStrings[i]);
        #else
            text.print(textStrings[i]);
        #endif
        textPositions[i] = text.getDimensions();
        textPositions[i] = centralise(textPositions[i], Vector2di(bounds.w,bounds.h));
        textPositions[i].y = t * bounds.h;
        t+=0.2f;
    }
    if(nameEntry)
    {
        if(score <= scores.getScore(9))
            nameEntry = false;
    }
}

ScoreScreen::~ScoreScreen()
{
    //dtor
    scores.saveScores(scoreFile);
}

void ScoreScreen::update()
{
    for(int i = emit.size()-1; i >=0; --i)
        emit.at(i).update();

    if(textStrings[1].size()>3)
    {
        //	turn name entry off
        nameEntry = false;

        //	Get rid of last letter
        textStrings[1][3]=0;

        //	Enter highscore into table
        scores.nameEntry(textStrings[1], score);
        textStrings[1].clear();
    }
}

#ifdef PENJIN_SDL
    void ScoreScreen::render(SDL_Surface* screen)
    {
        for(int i = emit.size()-1; i >=0; --i)
            emit[i].render(screen);

        if(nameEntry)
        {
            /// Display Name entry mode
            text.setColour(YELLOW);
            text.setPosition(textPositions[0]);
            if(textStrings[1].size()<3)
                textStrings[0][0] = currentLetter;
            else
                textStrings[0][0] = '?';
            text.print(screen, textStrings[0]);
            text.setPosition(textPositions[1]);
            text.setColour(WHITE);
            if(textStrings[1].size()<3)
                text.print(screen,textStrings[1]);
            else
                text.print(screen,textStrings[1] + " " + textStrings[2]);
            text.setPosition(textPositions[2]);
            text.setColour(BLUE);
            text.print(screen,(int)score);
            text.setPosition(textPositions[3]);
            text.setColour(ORANGE);
            text.print(screen,textStrings[3]);
        }
        else
        {
            /// Show Hi-Score table.
            scores.render(screen);
        }
    }
#else
    void ScoreScreen::render()
    {

        for(int i = emit.size()-1; i >=0; --i)
            emit[i].render();

        if(nameEntry)
        {
            /// Display Name entry mode
            text.setColour(YELLOW);
            text.setPosition(textPositions[0]);
            if(textStrings[1].size()<3)
                textStrings[0][0] = currentLetter;
            else
                textStrings[0][0] = '?';
            text.print(textStrings[0]);
            text.setPosition(textPositions[1]);
            text.setColour(WHITE);
            if(textStrings[1].size()<3)
                text.print(textStrings[1]);
            else
                text.print(textStrings[2]);
            text.setPosition(textPositions[2]);
            text.setColour(BLUE);
            text.print((int)score);
            text.setPosition(textPositions[3]);
            text.setColour(ORANGE);
            text.print(textStrings[3]);
        }
        else
        {
            /// Show Hi-Score table.
            scores.render();
        }
    }
#endif
Vector2di ScoreScreen::centralise(const Vector2di& a,Vector2di b)
{
    b-=a;
    b/=2;
    return b;
}
