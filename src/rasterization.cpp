#include "rasterization.h"
#include <iostream>

void drawTriangle(
                double x1, double y1, SDL_Color c1,
                double x2, double y2, SDL_Color c2,
                double x3, double y3, SDL_Color c3, SDL_Renderer* renderer){
    std::cout<<"drawing triangle: \n";
    std::cout<<"["<<x1<<" "<<y1<<"]\n";
    std::cout<<"["<<x2<<" "<<y2<<"]\n";
    std::cout<<"["<<x3<<" "<<y3<<"]\n";

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(renderer, x1, y1, x3, y3);
    

}

void drawTriangleMesh(
                double x1, double y1, SDL_Color c1,
                double x2, double y2, SDL_Color c2,
                double x3, double y3, SDL_Color c3, SDL_Renderer* renderer){
    std::cout<<"drawing triangle: \n";
    std::cout<<"["<<x1<<" "<<y1<<"]\n";
    std::cout<<"["<<x2<<" "<<y2<<"]\n";
    std::cout<<"["<<x3<<" "<<y3<<"]\n";

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(renderer, x1, y1, x3, y3);
}
