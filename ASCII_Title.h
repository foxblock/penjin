#ifndef ASCII_TITLE_H
#define ASCII_TITLE_H

/* ABOUT:
console application title Class written by Kevin Winfield-Pantoja
11.10.2005
*/
#include <string>
using std::string;
#include "PenjinTypes.h"
#include "Penjin.h"
#include "version.h"

class ASCII_Title
{
    public:
        ASCII_Title();
        ~ASCII_Title();
        void setTitle(CRstring appTitle);				//	Stores a title for the application
        void setVersion(CRstring appVersion);			//	stores a version number for the app
        void setDescription(CRstring appDescription){description = appDescription;}	//	stores a short description for the app
        void render();							        //	displays the title information

    private:
        string title;
        string version;
        string description;
};

#endif // ASCII_TITLE_H
