#include <vector>
#include <cmath>
#include "mathUtils.h"
#include "constants.h"


#ifndef MODEL2D
#define MODEL2D

/*
    model3d files are meant to containt:
        -Object3 implementation with coresponding transform functions (move, rotate, set position, scale)


*/

class Object2{
    std::vector<std::vector<Point2>>vertices;
    Vec2 axis;
    
public:
    Object2();
    Object2(std::vector<std::vector<Point2>>v);
    Object2(std::vector<std::vector<Point2>>v, Vec2 a);
    Object2(Vec2 a);
    void addVertices(std::vector<std::vector<Point2>>v);
    void setAxis(Vec2 a);
    std::vector<std::vector<Point2>>& getVertices();
    Vec2& getAxis();

    void rotate(double a);
    void move(Vec2 vec);
    void setPos(Vec2 vec);
    void scale(double x);
};

Vec2 determineAxis(Object2 object);

#endif