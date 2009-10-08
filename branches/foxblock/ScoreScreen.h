#ifndef SCORESCREEN_H
#define SCORESCREEN_H

#include "HiScore.h"
#include "Emitter.h"
#include "Text.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;
#include <vector>
using namespace std;
class ScoreScreen
{
    public:
        ScoreScreen();
        ScoreScreen(CRstring scoreFile);
        ~ScoreScreen();

        /// Font stuff
        PENJIN_ERRORS loadFont(CRstring font, CRuint size)
        {
            PENJIN_ERRORS result = text.loadFont(font,size+16);
            if(result != PENJIN_OK)
                return result;

            return scores.loadFont(font,size);
        }
        void setFontColour(Colour colour){text.setColour(colour);}
        void setBoundaries(SDL_Rect bounds){text.setBoundaries(bounds);this->bounds = bounds;}
        /// Table Font Stuff


        void init();
        void update();
        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);
            void render(){render(screen);}
        #else
            void render();
        #endif

        /// ScoreScreen specific stuff
        void setScore(CRuint score){this->score=score;}         //  Set the potential hi score
        void setNameEntry(CRbool ne){nameEntry = ne;}           //  Name entry mode or table display mode
        bool inNameEntryScreen()const{return nameEntry;}
        void setScoreFile(CRstring file){scoreFile = file;}
        void setTableTitle(CRstring title){scores.setTableTitle(title);}
        //  Input functions
        void charUp()
        {
            if(nameEntry)
            {
                if(currentLetter < 'Z')
                    ++currentLetter;
                else if(currentLetter == 'Z')
                    currentLetter = 'A';
            }
        }
        void charDown()
        {
            if(nameEntry)
            {
                if(currentLetter > 'A')
                    --currentLetter;
                else if(currentLetter == 'A')
                    currentLetter = 'Z';
            }

        }
        void charInput(){if(nameEntry)textStrings[1]+=currentLetter;}
        void charDelete(){if(textStrings[1].size()&& nameEntry)textStrings[1].erase(textStrings[1].begin()+textStrings[1].size()-1);}

    private:
        Vector2di centralise(const Vector2di& a, Vector2di b);
        Text text;
        Vector2di textPositions[4];
        string textStrings[4];
        vector<Emitter> emit;
        uint score;
        HiScore scores;
        bool nameEntry;
        string scoreFile;
        char currentLetter;
        SDL_Rect bounds;
        #ifdef PENJIN_SDL
            SDL_Surface* screen;
        #endif
};

#endif // SCORESCREEN_H
