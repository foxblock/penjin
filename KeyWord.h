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
