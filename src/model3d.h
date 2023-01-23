#include <vector>
#include <cmath>
#include "mathUtils.h"

#ifndef MODEL3D
#define MODEL3D

/*
    model3d files are meant to containt:
        -Object3 implementation with coresponding transform functions (move, rotate, set position, scale)


*/

class Object3{
    std::vector<std::vector<Point3>>vertices;
    Point3 axis;

public:
    Object3();
    Object3(std::vector<std::vector<Point3>>v);
    Object3(std::vector<std::vector<Vec3>>v);
    Object3(std::vector<std::vector<Point3>>v, Point3 a);
    Object3(Point3 a);
    void addVertices(std::vector<std::vector<Point3>>v);
    void setAxis(Point3 a);
    std::vector<std::vector<Point3>>& getVertives();
    Point3& getAxis();
};

//TODO:
    //rotating by 3 angles
    //moving by Vec3
    //setting the position using Vec3 (position of axis)
    //scale by a double value

#endif

