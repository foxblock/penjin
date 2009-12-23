#include "Penjin.h"

namespace Penjin
{
    string appName = "Penjin";
    #ifdef PLATFORM_WII
        string workingDir = "sd:/" + appName +"/";
    #endif
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
    /*if (chdir("sd:/"))
        return PenjinErrors::PENJIN_FAT_ACCESS_ROOT_FAILED;*/
    return PenjinErrors::PENJIN_OK;
}

PenjinErrors::PENJIN_ERRORS Penjin::canOpenRoot()
{
    DIR_ITER *root = diropen("sd:/");
    if (root)
    {
       dirclose(root);
       return PenjinErrors::PENJIN_OK;
    }
    return PenjinErrors::PENJIN_FAT_GET_ROOT_FAILED;
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

