#include <SDL2/SDL.h>
#include "mathUtils.h"

#define INT_BIG 20000000

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


#endif
