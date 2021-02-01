#include <iostream>
#include <conio.h>
#include "startUp.h"
#include "Interface.h"
#include "Player.h"



int main()
{
    //drawmaingameinterface(screenwidth, screenheight);
    startUp startup;

    while (startup.isRunning()) {
        // Update
        startup.update();

        //Render
        startup.render();
    }

    return 0;
}


