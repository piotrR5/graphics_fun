#include <vector>
#include <cmath>
#include "mathUtils.h"
#include "constants.h"


#ifndef MODEL3D
#define MODEL3D

/*
    model3d files are meant to containt:
        -Object3 implementation with coresponding transform functions (move, rotate, set position, scale)


*/

class Object3{
    std::vector<std::vector<Point3>>vertices;
    Vec3 axis;

public:
    Object3();
    Object3(std::vector<std::vector<Point3>>v);
    Object3(std::vector<std::vector<Vec3>>v);
    Object3(std::vector<std::vector<Point3>>v, Vec3 a);
    Object3(Vec3 a);
    void addVertices(std::vector<std::vector<Point3>>v);
    void addVertices(std::vector<std::vector<Vec3>>v);
    void setAxis(Vec3 a);
    void translate_object(Vec3 v);
    void scale_object(double scale);
    void set_object_position(Vec3 position);
    void rotate_object_x(double angle);
    void rotate_object_y(double angle);
    void rotate_object_z(double angle);
    std::vector<std::vector<Point3>>& getVertices();
    Vec3& getAxis();
};

Vec3 determineAxis(Object3 _object);

//TODO:
    //rotating by 3 angles

#endif

