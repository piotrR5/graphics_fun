#include "rasterization.h"
#include "3to2d.h"
#include "model2d.h"
#include "model3d.h"
#include "mathUtils.h"
#include <vector>
#include <iostream>


class Engine{
    /*
        it will contain all the sdl backend and objects info
    */
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int fps=60;
    int desiredDT=1000/fps;



    bool mainLoop();

    Engine();

    ~Engine();

};
