#ifndef PENJIN_H
#define PENJIN_H

/* The Penjin System Object
Handles setup and keeps track of useful global variables.
Also provides some quick init functions
*/

#include "ErrorHandler.h"
#include <dirent.h>

#ifdef PLATFORM_WII
    #include <fat.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
#else

#endif

namespace Penjin
{
    void setApplicationName(CRstring name);                     //  set the application name
    string getApplicationName();                                //  get the app name.
    PenjinErrors::PENJIN_ERRORS canOpenRoot();              //  tries to get the root directory of the FS
    #ifdef PLATFORM_WII
        PenjinErrors::PENJIN_ERRORS initFileSystem();           //  initialises SD card access.
        void deInitFileSystem();
        void setWorkingDirectory(CRstring dir);                 //  Set the dir that this program runs in
        string getWorkingDirectory();                           //  Get the program dir.
    #endif
}

#endif // PENJIN_H
