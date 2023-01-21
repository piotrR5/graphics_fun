#include <vector>
#include <cmath>
#include "mathUtils.h"

#ifndef MODEL2D
#define MODEL2D

class Object2{
    std::vector<std::vector<point2>>vertices;
    vec2 axis;
    
public:
    Object2();
    Object2(std::vector<std::vector<point2>>v);
    Object2(std::vector<std::vector<point2>>v, vec2 a);
    Object2(vec2 a);
    void addVertices(std::vector<std::vector<point2>>v);
    void setAxis(vec2 a);
    std::vector<std::vector<point2>>& getVertices();
    vec2& getAxis();




    void rotate(double a);
    void move(vec2 vec);
    void setPos(vec2 vec);
    void scale(double x);

    //TODO:
    //scale by a double value
};

#endif