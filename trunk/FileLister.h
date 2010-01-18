#ifndef FILELISTER_H
#define FILELISTER_H

/*
About: cross platform file and directory lister.
Parses directory and gives strings so you can load needed files.
*/

#ifdef _WIN32
    //#include <direct.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <stdlib.h>
    #define DT_DIR _S_IFDIR
    #define DT_REG _S_IFREG
#else
    #include <dirent.h>
    #include <unistd.h>
    //#include <sys/stat.h>
    #include <limits.h>
    #define _MAX_PATH PATH_MAX
    #ifdef PLATFORM_WII
        #define DT_DIR 4
        #define DT_REG 8
    #endif
#endif
#include "Menu.h"
#include "Parser.h"

class FileLister : public Menu
{
    public:
        FileLister();
        FileLister(CRstring startDir);
        virtual ~FileLister();

        virtual void render();
        virtual void update();

        string getPath()const{return workingDir;}
        void setPath(CRstring path){workingDir = path;}
        string getSelected();      //  Return the string of selected item
        vector<string> getListing();//  Return entire director listing as a vector of strings.
        string enter();             //  Enter the selected item(if directory) and return string of item.
        void goUp();                //  Go up one level in the directory tree

        void AddFilter(CRstring f){filters.push_back(f);}

    private:
        void createListing();   //  creates strings for dir listing.
        void createDisplay();   //  builds MenuItems to show listing.

        string workingDir;
        int folderDepth;
        vector<string> listing;
        vector<string> filters;
        enum DIR_TYPES
        {
            UNKNOWN=0,
            PATH
        };
        vector<int> listingTypes;

};

#endif // FILELISTER_H
