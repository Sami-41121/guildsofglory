#include <iostream>
#include "startUp.h"

int main()
{
    float screenWidth = 900.0, screenHeight = 600.0;
    startUp startup;

    while (startup.isRunning()) {
        // Update
        startup.update();

        //Render
        startup.render();
    }
    return 0;
}
