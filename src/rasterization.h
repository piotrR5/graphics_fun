#include <SDL2/SDL.h>
#include "mathUtils.h"

#define INT_BIG 20000000

#ifndef RASTERIZATION
#define RASTERIZATION

void drawPoint(point2 a, SDL_Renderer* renderer);

void drawLine(point2 a, point2 b, SDL_Renderer* renderer);

void drawLineBresenham(point2 a, point2 b, SDL_Renderer* renderer);

void drawTriangle(point2 a, point2 b, point2 c, SDL_Renderer* renderer);

void drawTriangleMesh(point2 a, point2 b, point2 c, SDL_Renderer* renderer);


#endif
