#ifndef STATEFILELIST_H
#define STATEFILELIST_H

#include "PenjinStates.h"
#include "FileLister.h"
#include "Sprite.h"

class StateFileList : public BaseState
{
    public:
        StateFileList();
        virtual ~StateFileList();

        virtual void init();

        virtual void render();
        virtual void update();
        virtual void userInput();

    private:
        FileLister list;
        string choice;
        bool loaded;
        Sprite test;
};

#endif // STATEFILELIST_H
