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
#ifndef KEYWORD_H_INCLUDED
#define KEYWORD_H_INCLUDED
#include "PenjinTypes.h"

class KeyWord
{
    public:
        KeyWord(){reset();}
        ~KeyWord(){reset();}
        KeyWord(CRstring keyWord){reset();this->keyWord = keyWord;}
        KeyWord(CRuint keyType){reset();this->keyType = keyType;}
        KeyWord(CRstring keyWord,CRuint keyType){reset();this->keyWord = keyWord;this->keyType = keyType;}

        void setKeyWord(CRstring keyWord){this->keyWord = keyWord;}
        void setKeyType(CRuint keyType){this->keyType = keyType;}
        void setNumNumerics(CRint num){numeric = num;}
        void setNumAlphas(CRint strings){this->strings = strings;}

        int getNumNumerics() const {return numeric;}
        int getNumAlphas() const {return strings;}
        string getKeyWord() const {return keyWord;}
        int getKeyType() const {return keyType;}

        bool operator==(CRstring keyWord)
        {
            if(keyWord == this->keyWord)
                return true;
            return false;
        }
        bool operator==(CRint keyType)
        {
            if(keyType == this->keyType)
                return true;
            return false;
        }
        KeyWord& operator=(CRstring keyWord)
        {
            setKeyWord(keyWord);
            return *this;
        }
        KeyWord& operator=(CRuint keyType)
        {
            setKeyType(keyType);
            return *this;
        }

    private:
        void reset()
        {
            keyWord = "NULL";
            keyType = -1;
            numeric = 0;
            strings = 0;
        }
        int keyType;   //  Stores an ID quivalent to the keyWord
        string keyWord; //  The string the parser looks for
        int numeric;    //  The number of numeric values to expect
        int strings;    //  The number of string values to expect
};
#endif // KEYWORD_H_INCLUDED
