#ifndef	ERRORHANDLER_H
#define	ERRORHANDLER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#if defined (PENJIN_ES) || defined (PENJIN_ES2)
    #ifdef PENJIN_ES
        #include <GLES/gl.h>
    #elif PENJIN_ES2
        #include <GLES2/gl2.h>
    #endif
    #include <EGL/egl.h>
#endif
#include <string>
using std::string;
#include <iostream>
using std::cout;

#include "PenjinErrors.h"
using namespace PenjinErrors;

#include "PenjinTypes.h"
class ErrorHandler
{
	public:
		ErrorHandler(){errorPrefix = "Penjin says: ";shouldGetTTF = false;}
		void setShouldGetTTF(CRbool check){shouldGetTTF = check;}
		void killApp(const PENJIN_ERRORS& e)
		{
		    std::cout << getErrorString(e);
		    exit(e);
        }
		string getErrorString(CRint errorCode)
		{
		    #ifndef PENJIN_ASCII
                string temp1;
                temp1 = checkSDL(errorCode);
                string temp2;
                temp2 = checkIMG(errorCode);
                string temp3;
                if(shouldGetTTF)
                    temp3 = checkTTF(errorCode);
                string out = errorPrefix + PENJIN_ERROR_STRINGS[errorCode+1] +
                (temp1.size()>1? temp1 : "") +
                (temp2.size()>1? temp2 : "");

                if(shouldGetTTF)
                    (temp3.size()>1? temp3 : "");
            #else
                string out = errorPrefix + PENJIN_ERROR_STRINGS[errorCode+1];
            #endif
		    return out + "\n";
		}
		void setErrorPrefix(CRstring prefix){errorPrefix = prefix;}
	private:
    #if defined (PENJIN_ES) || defined (PENJIN_ES2)
        // PUT GLES error checking here
    #endif
	#ifndef PENJIN_ASCII
        string checkSDL(CRint errorCode)
        {
            if(errorCode == PENJIN_SDL_SOMETHING_FAILED || errorCode == PENJIN_SDL_INVALID_COLORKEY ||errorCode == PENJIN_SDL_SETVIDEOMODE_FAILED ||errorCode == PENJIN_SDL_VIDEO_INIT_FAILED ||errorCode == PENJIN_SDL_VIDEO_QUERY_FAILED)
                return (string)" " + (string)SDL_GetError();
            return " ";
        }
        string checkIMG(CRint errorCode)
        {
            if(errorCode == PENJIN_IMG_UNABLE_TO_OPEN)
                return (string)" " + (string)IMG_GetError();
            return " ";
        }
        string checkTTF(CRint errorCode)
        {
            if(errorCode == PENJIN_TTF_UNABLE_TO_OPEN)
                return (string)" " + (string)TTF_GetError();
            return " ";
        }
    #endif
		string errorPrefix;
		bool shouldGetTTF;
};

#endif	//	ERRORHANDLER_H
