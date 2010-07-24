#ifndef HISCORE_H
#define HISCORE_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
#include "PenjinErrors.h"
using namespace PenjinErrors;
#include "PenjinTypes.h"
#include "Text.h"
#include "TextDoc.h"
#include "Encryption.h"
#include "StringUtility.h"

enum PENJIN_SCORE_MODES
{
	HIGH_TO_LOW,
	LOW_TO_HIGH
};


class HiScore
{
    public:
        HiScore();
        HiScore(CRuint numScores,CRuint numInitials);
        ~HiScore();
        void clear();

        void setMode(CRuint mode);						//	Sets the sorting mode of the highscore table
        void nameEntry(string name, uint score);	//	assigns a name to a specific score if it is good enough to be saved
        void setTableTitle(CRstring title){tableTitle = title;}
        void setBoundaries(const SDL_Rect& b);

        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);
        #else
            void render();
        #endif

        PENJIN_ERRORS saveScores(CRstring fileName);			//	Save scores to a textfile
        PENJIN_ERRORS loadScores(CRstring fileName);			//	load scores from a textfile

        PENJIN_ERRORS saveScoresBinary(CRstring fileName);	//	Save scores to a binary file
        PENJIN_ERRORS loadScoresBinary(CRstring fileName);	//	Load scores from a binary file

        void initialiseTables();						//	Clears the tables, ready to use.

        uint getScore(CRuint i)const
        {
            if(i < numScores)
                return scoreTable[i];

            return 0;
        }
        string getName(CRuint i)const{return nameTable[i];}
        uint getLastNameIndex()const{return lastNameIndex;}
        /// FONT STUFFs
        PENJIN_ERRORS loadFont(CRstring font,CRint size){return text.loadFont(font,size);}
        void setColour(Colour colour){text.setColour(colour);}

    private:
        uint numScores;
        uint numInitials;
        uint* scoreTable;
        string* nameTable;
        uint lastNameIndex;
        uint mode;
        TextDoc doc;
        Text text;
        Encryption crypt;
        string tableTitle;
        #ifndef PENJIN_3D
            Vector2di startPos;
            Vector2di endPos;
            Vector2df centrePos;
        #else
            Vector3df startPos;
            Vector3df endPos;
            Vector3df centrePos;
        #endif
};
#endif	//	HISCORE_H
