#include <vector>
#include <cmath>
#include "mathUtils.h"

#ifndef MODEL3D
#define MODEL3D

class Object3{
    std::vector<std::vector<point3>>vertices;
    point3 axis;
    

public:
    Object3();
    Object3(std::vector<std::vector<point3>>v);
    Object3(std::vector<std::vector<point3>>v, point3 a);
    Object3(point3 a);
    void addVertices(std::vector<std::vector<point3>>v);
    void setAxis(point3 a);
    std::vector<std::vector<point3>>& getVertives();
    point3& getAxis();
};

//TODO:
    //rotating by 3 angles
    //moving by vec3
    //setting the position using vec3 (position of axis)
    //scale by a double value

#endif

