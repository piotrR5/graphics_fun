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

    double mx=(double)640/1000;
    double my=(double)480/1000;

    point2 transformPoint(const point2& p);
    std::vector<std::vector<point2>>transformToFitScreen(const std::vector<std::vector<point2>>& obj);
    void draw(const std::vector<std::vector<point2>>& obj);
    void draw(const std::vector<std::vector<point2>>& obj, color_RGBA color);
    void draw(const std::vector<std::vector<point2>>& obj, bool wireframe);
    // void tranformToFitScreen();

    // void drawAll();

    // void addTriangle(point2 a, point2 b, point2 c);
    // void addTriangle(triangle2 t);
    // void popTriangle();
    // void removeTriangle(std::size_t i);

    // void addLine(point2 a, point2 b);
    // void addLine(line2 l);
    // void popLine();
    // void removeLine(std::size_t i);

    // void addPoint(point2 p);
    // void popPoint();
    // void removePoint(std::size_t i);



    bool mainLoop();

    Engine();

    ~Engine();

};
