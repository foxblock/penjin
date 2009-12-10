#ifndef TEXTDOC_H
#define TEXTDOC_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

#include "ErrorHandler.h"
#include "PenjinTypes.h"

#ifdef MEMWATCH
    #include "Memwatch.h"
#endif


class TextDoc
{
    public:
        TextDoc(){clear();}
        ~TextDoc(){clear();}
        uint size(){return docData.size();}
        PENJIN_ERRORS load(CRstring file);					//	Load a plain text file
        PENJIN_ERRORS save(CRstring file);					//	Save a plain text file
        void search(CRstring target);				//	Search for a string in the doc
        void editLine(CRint line, CRstring newData);//	replace a line of data with new data
        string getLine(CRint line);				//	get the string data of the line
        void viewDoc();							//	View an outline of the doc
        void clear();							//	Clear data out of doc.
        void append(CRstring data);				//	adds a string to the document
    private:
        int findLine(CRstring target);
        vector <string> docData;
};

#endif	//	TEXTDOC_H
