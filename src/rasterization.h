#include <SDL2/SDL.h>

#ifndef RASTERIZATION
#define RASTERIZATION

void draw(double x, double y, SDL_Color c);

void drawLine(double x1, double y1, SDL_Color c2, double x2, double y2, SDL_Color c1);

void drawTriangle(
                double x1, double y1, SDL_Color c1,
                double x2, double y2, SDL_Color c2,
                double x3, double y3, SDL_Color c3,
                SDL_Renderer* renderer);
    
void drawTriangleMesh(double x1, double y1, SDL_Color c1,
                double x2, double y2, SDL_Color c2,
                double x3, double y3, SDL_Color c3,
                SDL_Renderer* renderer);




#endif
