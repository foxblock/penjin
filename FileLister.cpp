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
    checkFolderDepth = true;
}

FileLister::FileLister(CRstring startDir)
{
    workingDir = startDir;
    createListing();
    folderDepth = -1;
    checkFolderDepth = true;
}

FileLister::~FileLister()
{
    //dtor
}

void FileLister::createListing()
{
    DIR* dir = NULL;
    dirent* dirEnt;
    dir = opendir(workingDir.c_str());
    if(!dir)
        return;

    listing.clear();
    listingTypes.clear();
    listing.push_back(workingDir);
    listingTypes.push_back(PATH);
    while((dirEnt = readdir(dir)))
    {
        if(filters.size() == 0)
        {
            int type = -1;
            string choice = dirEnt->d_name;
            #ifdef _WIN32
                struct stat fileStat;
                stat(string(workingDir + "/" + dirEnt->d_name).c_str(),&fileStat);
                if(fileStat.st_mode & DT_DIR)
                    type=DT_DIR;
                else if(fileStat.st_mode & DT_REG)
                    type=DT_REG;
                else
                    type=UNKNOWN;
            #else
                if(dirEnt->d_type == DT_DIR)
                    type=DT_DIR;
                else if(dirEnt->d_type == DT_REG)
                    type=DT_REG;
                else
                    type=UNKNOWN;
            #endif
            listing.push_back(choice);
            listingTypes.push_back(type);
        }
        else
        {
            for(int f = filters.size()-1; f>=0; --f)
            {
                int type = -1;
                string choice = dirEnt->d_name;
                #ifdef _WIN32
                    struct stat fileStat;
                    stat(string(workingDir + "/" + dirEnt->d_name).c_str(),&fileStat);
                    if(fileStat.st_mode & DT_DIR)
                        type=DT_DIR;
                    else if(fileStat.st_mode & DT_REG)
                        type=DT_REG;
                    else
                        type=UNKNOWN;
                #else
                    if(dirEnt->d_type == DT_DIR)
                        type=DT_DIR;
                    else if(dirEnt->d_type == DT_REG)
                        type=DT_REG;
                    else
                        type=UNKNOWN;
                #endif
                if( (filters.at(f) == "DIR" && type == DT_DIR) || choice.find("." + filters.at(f)) != choice.npos)
                {
                    listing.push_back(choice);
                    listingTypes.push_back(type);
                }
            }
        }
    }
    closedir(dir);
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
    string t = getSelected();
    if(t == "..")       //  Same as goUp()
        goUp();
    else if(t == ".")   //  This directory.
        return t;
    else if(((DirMenuItem*)menuItems.at(getSelection()))->getDirType() == DT_DIR)
    {
        #ifdef _WIN32
            workingDir+= ("\\" + t);
        #else
            workingDir+= ("/" + t);
        #endif
        createListing();
        clear();
        ++folderDepth;
        #ifdef _DEBUG
        cout << "FD: " << folderDepth << endl;
        #endif
    }
    #ifdef _WIN32
        return getPath() + ("\\" + t);
    #else
        return getPath() + ("/" + t);
    #endif
}

void FileLister::goUp()
{
    if(folderDepth>=0 || !checkFolderDepth)
    {
        workingDir = Parser().getParentDirectory(workingDir);
        size_t back = workingDir.size()-1;
        if(workingDir.at(back) == '/' || workingDir.at(back) == '\\')
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
