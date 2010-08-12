#include "Menu.h"

Menu::Menu()
{
    #ifndef PENJIN_ASCII
        text = NULL;
    #endif
    currentSelection = 0;
    correction = 0;
    #ifdef PENJIN_3D
        menu3D = false;
        angle = 0.0f;
        angleDelta = 0.1f;
        menuStart = Vector3df(0,0,0);
    #else
        menuStart = Vector2di(0,0);
    #endif
    #ifdef PENJIN_SDL
        screen = GFX::getVideoSurface();
    #endif

}

Menu::~Menu()
{
    #ifndef PENJIN_ASCII
        if(text)
        {
            delete text;
            text = NULL;
        }
    #endif
    clear();
}

void Menu::update()
{
    #ifdef PENJIN_3D
        if(menu3D)
        {
            angle+= angleDelta;
        }
    #endif
    for(int i = menuItems.size()-1; i >= 0; --i)
    {
        if(currentSelection == i)
        {
            menuItems[i]->setIsSelected(true);
            #ifdef PENJIN_3D
                if(menu3D)
                {
                    menuItems[i]->setAngle(&angle);
                    menuItems[i]->setMenu3D(true);
                }
            #endif
        }
        else
        {
            menuItems[i]->setIsSelected(false);
            #ifdef PENJIN_3D
                menuItems[i]->setMenu3D(false);
            #endif
        }
        #ifndef PENJIN_ASCII
            int type = menuItems[i]->getType();
            if(type == MENU_STRING_ITEM)
                ((StringMenuItem*)menuItems[i])->setTextSelectionColour(textSelectionColour);
            else if (type == MENU_DIR_ITEM)
                ((DirMenuItem*)menuItems[i])->setTextSelectionColour(textSelectionColour);
            else if (type == MENU_IMAGE_STRING_ITEM)
                ((ImageStringMenuItem*)menuItems[i])->setTextSelectionColour(textSelectionColour);
            else if (type == MENU_ANIM_STRING_ITEM)
                ((AnimationStringMenuItem*)menuItems[i])->setTextSelectionColour(textSelectionColour);
        #endif
        menuItems[i]->update();
    }
}

#ifdef PENJIN_SDL
    void Menu::render(SDL_Surface* screen)
    {
        for(int i = menuItems.size()-1; i >= 0; --i)
            menuItems[i]->render(screen);
    }
#else
    void Menu::render()
    {
        #ifdef PENJIN_ASCII
            for(int i = 0; i< menuItems.size(); ++i)
            {
                if(menuItems[i]->getIsSelectable())
                    cout << "#" << i << " ";
                menuItems[i]->render();
            }
        #else
            for(int i = menuItems.size()-1; i >= 0; --i)
                menuItems[i]->render();
        #endif
    }
#endif

bool Menu::setMouseSelection(CRint x,CRint y)
{
    for(int i = menuItems.size()-1; i >=0; --i)
    {
        if(menuItems[i]->isMouseSelected(x,y))
        {
            //  Select the selectable selection
            currentSelection = i;
            return true;
        }
    }
    return false;
}

void Menu::menuUp()
{
    int I = 1;
    while (currentSelection - I >= 0)
    {
        if (menuItems[currentSelection - I]->getIsSelectable())
        {
            currentSelection -= I;
            return;
        }
        else
            ++I;
    }
}

void Menu::menuDown()
{
    int I = 1;
    while (currentSelection + I < (int)menuItems.size())
    {
        if (menuItems[currentSelection + I]->getIsSelectable())
        {
            currentSelection += I;
            return;
        }
        else
            ++I;
    }
}

void Menu::addItem(CRint type)
{
    MenuItem* item;
    item = NULL;
    menuItems.push_back(item);
    int s = menuItems.size()-1;

    if (type == MENU_STRING_ITEM)
    {
        menuItems[s] = new StringMenuItem;
        #ifndef PENJIN_ASCII
            ((StringMenuItem*)menuItems[s])->setTextHandler(text);
        #endif
    }
    else if (type == MENU_DIR_ITEM)
    {
        menuItems[s] = new DirMenuItem;
        #ifndef PENJIN_ASCII
            ((DirMenuItem*)menuItems[s])->setTextHandler(text);
        #endif
    }
    #ifndef PENJIN_ASCII
        else if (type == MENU_IMAGE_ITEM)
            menuItems[s] = new ImageMenuItem;
        else if (type == MENU_ANIM_ITEM)
            menuItems[s] = new AnimationMenuItem;
        else if (type == MENU_ANIM_STRING_ITEM)
        {
            menuItems[s] = new AnimationStringMenuItem;
            ((AnimationStringMenuItem*)menuItems[s])->setTextHandler(text);
        }
        else if (type == MENU_IMAGE_STRING_ITEM)
        {
            menuItems[s] = new ImageStringMenuItem;
            ((ImageStringMenuItem*)menuItems[menuItems.size()-1])->setTextHandler(text);
        }
    #endif
    else if(type == MENU_ITEM)
        menuItems[s] = new MenuItem;
    updatePositions();
}

void Menu::updatePositions()
{
    int s = menuItems.size()-1;
    //  Check for first MenuItem
    menuItems[s]->setPosition(menuStart);
    for(int i = s; i >= 0 ; --i)
    {
        if (s != 0)
        {
            #ifdef PENJIN_3D
                Vector3df pos = menuItems[s-1]->getPosition();
                pos.y += (menuItems[s-1]->getSpacing() - menuItems[s-1]->getDimensions().y);
            #else
                Vector2df pos = menuItems[s-1]->getPosition();
                pos.y += (menuItems[s-1]->getSpacing() + menuItems[s-1]->getDimensions().y);
            #endif
            menuItems[s]->setPosition(pos);
        }
    }
}

void Menu::clear()
{
    for(int i = menuItems.size()-1; i >= 0; --i)
        removeItem(i);

    menuItems.clear();
}

void Menu::removeItem(CRint itemNum)
{
    int size = menuItems.size();
    if(size <= itemNum)
        return;
    if(menuItems[itemNum])
    {
        delete menuItems[itemNum];
        menuItems[itemNum] = NULL;
        menuItems.erase(menuItems.begin() + itemNum);
    }
}

void Menu::removeItem()
{
    int size = menuItems.size();
    if(size)
        removeItem(size-1);
}

#ifndef PENJIN_ASCII
    PENJIN_ERRORS Menu::loadFont(CRstring fontName,CRint fontSize)
    {
        //  Check for the existence of the Text
        if(text)
        {
            text->clear();
            delete text;
        }
        text = NULL;
        text = new Text;

        //  we want to control the absolute position of the text at all times.
        text->setRelativity(false);

        return text->loadFont(fontName, fontSize);
    }
    void Menu::setTextColour(const Colour& col)
    {
        //  Text not init'd
        if(!text)
            return;
        text->setColour(col);
    }
    PENJIN_ERRORS Menu::loadImage(CRstring fileName){return loadImage(menuItems.size()-1, fileName);}
    PENJIN_ERRORS Menu::loadImage(CRuint index,CRstring fileName)
    {
        if(index >= menuItems.size())
            return PENJIN_INVALID_INDEX;
        int type = menuItems[index]->getType();
        if(type == MENU_IMAGE_ITEM)
            return ((ImageMenuItem*)menuItems[index])->loadImage(fileName);
        else if(type == MENU_IMAGE_STRING_ITEM)
            return ((ImageStringMenuItem*)menuItems[index])->loadImage(fileName);
        return PENJIN_INVALID_MENUITEM_TYPE;
    }

    PENJIN_ERRORS Menu::loadFrame(CRuint index,CRstring fileName)
    {
        if(index >= menuItems.size())
            return PENJIN_INVALID_INDEX;
        int type = menuItems[index]->getType();
        if(type == MENU_ANIM_ITEM)
            return ((AnimationMenuItem*)menuItems[index])->loadFrame(fileName);
        else if(type == MENU_ANIM_STRING_ITEM)
            return ((AnimationStringMenuItem*)menuItems[index])->loadFrame(fileName);
        return PENJIN_INVALID_MENUITEM_TYPE;
    }

    PENJIN_ERRORS Menu::loadFrame(CRstring fileName){return loadFrame(menuItems.size()-1, fileName);}

    PENJIN_ERRORS Menu::loadFrames(CRuint index,CRstring fileName,CRuint xTiles,CRuint yTiles)
    {
        if(index >= menuItems.size())
            return PENJIN_INVALID_INDEX;
        int type = menuItems[index]->getType();
        if(type == MENU_ANIM_ITEM)
            return ((AnimationMenuItem*)menuItems[index])->loadFrames(fileName, xTiles, yTiles);
        else if(type == MENU_ANIM_STRING_ITEM)
            return ((AnimationStringMenuItem*)menuItems[index])->loadFrames(fileName, xTiles, yTiles);
        return PENJIN_INVALID_MENUITEM_TYPE;
    }

    PENJIN_ERRORS Menu::loadFrames(CRstring tileSheet,CRuint xTiles,CRuint yTiles){return loadFrames(menuItems.size()-1,tileSheet, xTiles, yTiles);}
    PENJIN_ERRORS Menu::loadSelectionFrame(CRstring fileName){return loadSelectionFrame(menuItems.size()-1, fileName);}
    PENJIN_ERRORS Menu::loadSelectionFrame(CRuint index,CRstring fileName)
    {
        if(index >= menuItems.size())
            return PENJIN_INVALID_INDEX;
        int type = menuItems[index]->getType();
        if(type == MENU_ANIM_ITEM)
            return ((AnimationMenuItem*)menuItems[index])->loadSelectionFrame(fileName);
        else if(type == MENU_ANIM_STRING_ITEM)
            return ((AnimationStringMenuItem*)menuItems[index])->loadSelectionFrame(fileName);
        return PENJIN_INVALID_MENUITEM_TYPE;
    }

    PENJIN_ERRORS Menu::loadSelectionImage(CRuint index,CRstring fileName)
    {
        if(index >= menuItems.size())
            return PENJIN_INVALID_INDEX;
        int type = menuItems[index]->getType();
        if(type == MENU_IMAGE_ITEM)
            return ((ImageMenuItem*)menuItems[index])->loadSelection(fileName);
        else if(type == MENU_IMAGE_STRING_ITEM)
            return ((ImageStringMenuItem*)menuItems[index])->loadSelection(fileName);
        return PENJIN_INVALID_MENUITEM_TYPE;
    }

    PENJIN_ERRORS Menu::loadSelectionImage(CRstring fileName){return loadSelectionImage(menuItems.size()-1, fileName);}
    PENJIN_ERRORS Menu::loadSelectionFrames(CRstring tileSheet,CRuint xTiles,CRuint yTiles){return loadSelectionFrames(menuItems.size()-1, tileSheet, xTiles, yTiles);}
    PENJIN_ERRORS Menu::loadSelectionFrames(CRuint index,CRstring tileSheet,CRuint xTiles,CRuint yTiles)
    {
        if(index >= menuItems.size())
            return PENJIN_INVALID_INDEX;
        int type = menuItems[index]->getType();
        if(type == MENU_ANIM_ITEM)
            return ((AnimationMenuItem*)menuItems[index])->loadSelectionFrames(tileSheet,xTiles,yTiles);
        else if(type == MENU_ANIM_STRING_ITEM)
            return ((AnimationStringMenuItem*)menuItems[index])->loadSelectionFrames(tileSheet, xTiles, yTiles);
        return PENJIN_INVALID_MENUITEM_TYPE;
    }
    void Menu::centreText()
    {
        for(int s = menuItems.size()-1; s>=0; --s)
        {
            MENU_TYPES type = menuItems[s]->getType();
            if (type == MENU_ANIM_STRING_ITEM)
                ((AnimationStringMenuItem*)menuItems[s])->centreText(correction);
            else if (type == MENU_IMAGE_STRING_ITEM)
                ((ImageStringMenuItem*)menuItems[s])->centreText(correction);
        }
    }
#endif
void Menu::setMenuItemText(CRuint item,CRstring txt)
{
    #ifndef PENJIN_ASCII
        //  Text not init'd
        if(!text)
            return;
    #endif
    //  MenuItem out of array boundary
    if(item >= menuItems.size())
        return;

    int type = menuItems[item]->getType();
    if(type == MENU_STRING_ITEM)
        ((StringMenuItem*)menuItems[item])->setMenuItemText(txt);
    else if(type == MENU_DIR_ITEM)
        ((DirMenuItem*)menuItems[item])->setMenuItemText(txt);
#ifndef PENJIN_ASCII
    else if(type == MENU_ANIM_STRING_ITEM)
        ((AnimationStringMenuItem*)menuItems[item])->setMenuItemText(txt);
    else if (type == MENU_IMAGE_STRING_ITEM)
        ((ImageStringMenuItem*)menuItems[item])->setMenuItemText(txt);
#endif
}

void Menu::setMenuItemText(CRstring itemText){setMenuItemText(menuItems.size()-1, itemText);}

void Menu::setIsSelectable(CRuint item,CRbool selectable)
{
    if(item >= menuItems.size())
        return;
    menuItems[item]->setIsSelectable(selectable);
}

void Menu::setIsSelectable(CRbool selectable){setIsSelectable(menuItems.size()-1, selectable);}

void Menu::setSpacing(CRuint index,CRint spacing)
{
    if(index >= menuItems.size())
        return;
    menuItems[index]->setSpacing(spacing);
    updatePositions();
}

void Menu::setSpacing(CRint spacing){setSpacing(menuItems.size()-1,spacing);}

void Menu::setHorizontalOffset(CRuint index,CRint offset)
{
    if(index >= menuItems.size())
        return;
    menuItems[index]->setHorizontalOffset(offset);
}

void Menu::setHorizontalOffset(CRint offset){setHorizontalOffset(menuItems.size()-1,offset);}

void Menu::setSelectionIndicator(CRuint index,CRchar c)
{
    if(index >= menuItems.size())
        return;
    int type = menuItems[index]->getType();
    if(type == MENU_STRING_ITEM)
        ((StringMenuItem*)menuItems[index])->setSelectionIndicator(c);
#ifndef PENJIN_ASCII
    else if (type == MENU_ANIM_STRING_ITEM)
        ((AnimationStringMenuItem*)menuItems[index])->setSelectionIndicator(c);
    else if (type == MENU_IMAGE_STRING_ITEM)
        ((ImageStringMenuItem*)menuItems[index])->setSelectionIndicator(c);
#endif
}

void Menu::setSelectionIndicator(CRchar c)
{
    for(int i = menuItems.size()-1; i>=0; --i)
        setSelectionIndicator(i,c);
}

#ifdef PENJIN_SDL
    void Menu::setUseHardware(CRbool use)
    {
        for(int i = menuItems.size()-1; i >=0; --i)
        {
            MENU_TYPES type = menuItems[i]->getType();
            if(type == MENU_IMAGE_ITEM)
                ((ImageMenuItem*)menuItems[i])->setUseHardware(use);
            else if(type == MENU_IMAGE_STRING_ITEM)
                ((ImageStringMenuItem*)menuItems[i])->setUseHardware(use);
            else if(type == MENU_ANIM_ITEM)
                ((AnimationMenuItem*)menuItems[i])->setUseHardware(use);
            else if(type == MENU_ANIM_STRING_ITEM)
                ((AnimationStringMenuItem*)menuItems[i])->setUseHardware(use);
        }
    }
#endif

#ifdef PENJIN_3D
 void Menu::setMenuItemDimensions(CRuint i,const Vector2di& dims){menuItems[i]->setDimensions(dims);}
#endif

