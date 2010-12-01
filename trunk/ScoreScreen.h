/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
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
        void charInput(uchar l);
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
