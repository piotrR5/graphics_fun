#include "rasterization.h"
#include <iostream>

void drawTriangle(
                double x1, double y1, SDL_Color c1,
                double x2, double y2, SDL_Color c2,
                double x3, double y3, SDL_Color c3){
    std::cout<<"drawing triangle: \n";
    std::cout<<"["<<x1<<" "<<y1<<"]\n";
    std::cout<<"["<<x2<<" "<<y2<<"]\n";
    std::cout<<"["<<x3<<" "<<y3<<"]\n";

}
