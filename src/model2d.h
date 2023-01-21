#include <vector>
#include <cmath>
#include "mathUtils.h"

#ifndef MODEL2D
#define MODEL2D

class Object2{
    std::vector<std::vector<point2>>vertices;
    point2 axis;
    

public:
    Object2();
    Object2(std::vector<std::vector<point2>>v);
    Object2(std::vector<std::vector<point2>>v, point2 a);
    Object2(point2 a);
    void addVertices(std::vector<std::vector<point2>>v);
    void setAxis(point2 a);
    std::vector<std::vector<point2>>& getVertices();
    point2& getAxis();

    //TODO:
    //rotating by 2 angles
    //moving by vec2
    //setting the position using vec2 (position of axis)
    //scale by a double value
};

#endif