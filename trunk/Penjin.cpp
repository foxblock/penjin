#include "Penjin.h"

namespace Penjin
{
    string appName = "Penjin";
    #ifdef PLATFORM_WII
        string workingDir = "sd/" + appName +"/";
    #endif
}

PenjinErrors::PENJIN_ERRORS Penjin::canOpenRoot()
{
    #ifdef PLATFORM_WII
        DIR_ITER *root = diropen("sd/");
    #elif _WIN32
        DIR *root = opendir("C:\\");
    #else // _LINUX
        DIR *root = opendir("/");
    #endif
    if (root)
    {
        #ifdef PLATFORM_WII
            dirclose(root);
        #elif _WIN32
            closedir(root);
        #else // _LINUX
            closedir(root);
        #endif

       return PenjinErrors::PENJIN_OK;
    }
    return PenjinErrors::PENJIN_FAT_GET_ROOT_FAILED;
}

#ifdef PLATFORM_WII
PenjinErrors::PENJIN_ERRORS Penjin::initFileSystem()
{
    PenjinErrors::PENJIN_ERRORS e;
    if (!fatInitDefault())
        return PenjinErrors::PENJIN_FAT_INIT_FAILED;
    e = canOpenRoot();
    if (e!= PenjinErrors::PENJIN_OK)
        return e;
    /*if (chdir("sd/"))
        return PenjinErrors::PENJIN_FAT_ACCESS_ROOT_FAILED;*/
    return PenjinErrors::PENJIN_OK;
}

void Penjin::setWorkingDirectory(CRstring dir)
{
    workingDir = dir;
}

string Penjin::getWorkingDirectory()
{
    return workingDir;
}

void Penjin::deInitFileSystem()
{
    fatUnmount(0);                  //  Unmount the FAT system from whatever stage it may be.
}
#endif


void Penjin::setApplicationName(CRstring n)
{
    appName = n;
}

string Penjin::getApplicationName()
{
    return appName;
}

