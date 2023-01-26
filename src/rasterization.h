#include <SDL2/SDL.h>
#include "mathUtils.h"
#include "constants.h"
#include "model2d.h"
#include "model3d.h"




#ifndef RASTERIZATION
#define RASTERIZATION

/*
    this file contains low level functions to draw different entities
*/

void drawPoint(Point2 a, SDL_Renderer* renderer);

void drawPoint(Point2 a, Color_RGBA color, SDL_Renderer* renderer);

void drawLine(Point2 a, Point2 b, SDL_Renderer* renderer);

void drawLine(Point2 a, Point2 b, Color_RGBA color, SDL_Renderer* renderer);

void drawLineBresenham(Point2 a, Point2 b, SDL_Renderer* renderer);

void drawTriangle(Point2 a, Point2 b, Point2 c, SDL_Renderer* renderer);

void drawTriangle(Point2 a, Point2 b, Point2 c, Color_RGBA color, SDL_Renderer* renderer);

void drawTriangleMesh(Point2 a, Point2 b, Point2 c, SDL_Renderer* renderer);

void drawTriangleMesh(Point2 a, Point2 b, Point2 c, Color_RGBA color, SDL_Renderer* renderer);

/*
    functions that transform 2D plane objects to fit the screen
*/

Point2 transformPoint(const Point2& p);

std::vector<Object2>transformToFitScreen(std::vector<Object2> obj);


#endif
