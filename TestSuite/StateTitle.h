#ifndef STATETITLE_H
#define STATETITLE_H

#include "PenjinStates.h"

#include "Menu.h"

class StateTitle : public BaseState
{
    public:
        StateTitle();
        virtual void init();
        virtual ~StateTitle();

        virtual void render();
        virtual void update();
        virtual void userInput();

    private:
        Menu menu;
        int choice;
        void initMenu();
        void menuLogic();
};

#endif // STATETITLE_H
