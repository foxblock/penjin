#ifndef SCORE_H
#define SCORE_H

#include "PenjinTypes.h"

class Score
{
    public:
        Score();
        int getScore()const;					    //	returns the current score
        void changeScore(CRint points);		//	change score by set number of points
        void setMultiplier(CRint mult);	    //	set a value for a score multiplier
        int getMultiplier()const;				//	gets the current multiplier
        void increaseMultiplier();		    //  increase multiply by 1
        void resetScore();			        //	Resets the score
        void storeScore();			        //	Stores the current score
        int getDifference()const;			    //	Returns the difference
    private:
        int score;
        int multiplier;
        int lastScore;
};
#endif	//	SCORE_H
