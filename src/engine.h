#include "rasterization.h"
#include "3to2d.h"
#include "model2d.h"
#include "model3d.h"
#include "mathUtils.h"
#include "shader.h"
#include <vector>
#include <iostream>

#include "constants.h"

/*
    engine.h file is meant to contain implementation of drawing functions (functions to diffrently draw triangles, lines, objects etc)
    it also contains the main program loop and is the life place of SDL_Window
*/

class Engine{

public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int fps=60;
    int desiredDT=1000/fps;
    Camera camera;

    void eventHandler(bool& run);

    /*
        draw function invokes rasterization functions to draw every 2D object
    */
    void draw(std::vector<Object2> obj, uint8_t mode, Color_RGBA color);
    // void draw(std::vector<Object2> obj, Color_RGBA (*shader)(int i));
    

    bool mainLoop();

    Engine();

    ~Engine();
};
