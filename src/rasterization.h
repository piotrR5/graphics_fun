#include <SDL2/SDL.h>
#include "mathUtils.h"

#ifndef RASTERIZATION
#define RASTERIZATION

void transformToFitScreen(std::vector<point2*>points);

void drawPoint(point2 a, SDL_Renderer* renderer);

void drawLine(point2 a, point2 b, SDL_Renderer* renderer);

void drawLineBresenham(point2 a, point2 b, SDL_Renderer* renderer);

void drawTriangle(point2 a, point2 b, point2 c, SDL_Renderer* renderer);


#endif
