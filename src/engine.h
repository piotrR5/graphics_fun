#include "rasterization.h"
#include "3to2d.h"
#include "model2d.h"
#include "model3d.h"
#include "mathUtils.h"
#include "shader.h"
#include <vector>
#include <iostream>

#define DRAW_WIREFRAME_NORMAL 1
#define DRAW_WIREFRAME_COLOR 2
#define DRAW_NORMAL 3
#define DRAW_COLOR 4

#define NULL_COLOR {0,0,0,255}

class Engine{

public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int fps=60;
    int desiredDT=1000/fps;

    double mx=(double)640/1000;
    double my=(double)480/1000;

    Point2 transformPoint(const Point2& p);
    std::vector<Object2>transformToFitScreen(std::vector<Object2> obj);
    void draw(std::vector<Object2> obj, uint8_t mode, Color_RGBA color);
    // void draw(std::vector<Object2> obj, Color_RGBA (*shader)(int i));
    

    bool mainLoop();

    Engine();

    ~Engine();

};
