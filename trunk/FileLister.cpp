#include "FileLister.h"

FileLister::FileLister()
{
    //ctor
    char* temp;
    temp = new char[_MAX_PATH];
    temp = getcwd(temp,_MAX_PATH);
    workingDir = temp;
    delete [] temp;
    createListing();
    folderDepth = -1;
}

FileLister::FileLister(CRstring startDir)
{
    workingDir = startDir;
    createListing();
    folderDepth = -1;
}

FileLister::~FileLister()
{
    //dtor
}

void FileLister::createListing()
{
   // #ifdef _WIN32

    //#else
        DIR* dir = NULL;
        dirent* dirEnt;
        dir = opendir(workingDir.c_str());
        if(!dir)
            return;

        listing.clear();
        listingTypes.clear();
        listing.push_back(workingDir);
        listingTypes.push_back(PATH);
        while(dirEnt = readdir(dir))
        {
            listing.push_back(dirEnt->d_name);
            #ifdef _DEBUG
            cout << dirEnt->d_name << endl;
            #endif

            #ifdef _WIN32
                struct stat fileStat;
                stat(string(workingDir + "/" + dirEnt->d_name).c_str(),&fileStat);
                if(fileStat.st_mode == DIRECTORY)
                    listingTypes.push_back(DIRECTORY);
                else if(fileStat.st_mode == FILE)
                    listingTypes.push_back(FILE);
                else
                    listingTypes.push_back(UNKNOWN);
            #else
                if(dirEnt->d_type == DIRECTORY)
                    listingTypes.push_back(DIRECTORY);
                else if(dirEnt->d_type == FILE)
                    listingTypes.push_back(FILE);
                else
                    listingTypes.push_back(UNKNOWN);
            #endif
        }
        closedir(dir);
   // #endif
}

void FileLister::createDisplay()
{
    if(listing.empty())
        createListing();

    clear();
    #ifdef _DEBUG
        cout << "Size: " << listing.size() << endl;
    #endif
    for(uint i = 0; i<listing.size(); ++i)
    {
        addItem(MENU_DIR_ITEM);
        #ifdef _DEBUG
        cout << "at(" << i << ") - " <<listing.at(i) << endl;
        #endif
        setMenuItemText(listing.at(i));
        if(i != 0)
            setIsSelectable(true);
        else
            setIsSelectable(false);
        ((DirMenuItem*)menuItems.back())->setDirType(listingTypes.at(i));
    }
    setSelection(1);
}

string FileLister::getSelected()
{
    return listing.at(getSelection());
}

string FileLister::enter()
{
   /* createListing();
    createDisplay();*/
    string t = getSelected();
    if(t == "..")       //  Same as goUp()
        goUp();
    else if(t == ".")   //  This directory.
        return t;
    else if(((DirMenuItem*)menuItems.at(getSelection()))->getDirType() == DIRECTORY)
    {
        workingDir+= ("/" + t);
        createListing();
        clear();
        ++folderDepth;
        #ifdef _DEBUG
        cout << "FD: " << folderDepth << endl;
        #endif
    }
    return t;
}

void FileLister::goUp()
{
    if(folderDepth>=0)
    {
        workingDir = Parser().getParentDirectory(workingDir);
        size_t back = workingDir.size()-1;
        if(workingDir.at(back) == '/')
            workingDir.resize(back);
        createListing();
        clear();
        --folderDepth;
        #ifdef _DEBUG
        cout << "FD: " << folderDepth << endl;
        #endif
    }
}

void FileLister::update()
{
    if(listing.empty())
        createListing();
    ((Menu*)this)->update();
}

void FileLister::render()
{
    if(empty())
        createDisplay();

    ((Menu*)this)->render();
}
