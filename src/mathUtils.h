#include <vector>
#include <cmath>
#include <iostream>
#include "constants.h"


#ifndef MATHUTILS
#define MATHUTILS
using namespace std;

/*
    this file contains basic implementation of mathematical and utility entities on which other parts of the project depend on
*/

struct Color_RGBA{
    uint8_t r=0, g=0, b=0, a=255;
};

struct Vec3f{
    float x;
    float y;
    float z;
};

struct Vec4{
    double x=0, y=0, z=0, w=0;
    void add(Vec4 v);
};

struct Vec3{
    double x=0, y=0, z=0;
    void add(Vec3 v);
};

struct Vec2{
    double x=0, y=0;
    void add(Vec2 v);
};

struct Point3{
    double x=0,y=0,z=0;
    Color_RGBA color;

    void add(Vec3 v);

    Vec3 makeVec3();

    Point3(double x, double y, double z);
    Point3(Vec3 v);
    Point3();
};

struct Line3{
    Point3 a,b;
    Line3();
    Line3(Point3 a, Point3 b);
};

struct Triangle3{
    Point3 a,b,c;
    Triangle3();
    Triangle3(Point3 a, Point3 b, Point3 c);
};

struct Triangle3_STL{
    Vec3 a,b,c,normal;
};

struct Point2{
    double x=0,y=0;
    Color_RGBA color;

    void add(Vec2 v);

    Vec2 makeVec2();

    Point2(Vec2 v, Color_RGBA c);
    Point2(Vec2 v);
    Point2(double x, double y, Color_RGBA c);
    Point2(double x, double y);
    Point2();
};

struct Line2{
    Point2 a,b;
    Line2();
    Line2(Point2 a, Point2 b);
};

struct Triangle2{
    Point2 a,b,c;
    Triangle2();
    Triangle2(Point2 a, Point2 b, Point2 c);
};

class Matrix3{
    vector<vector<double>> data;

    public:
    Matrix3();
    Matrix3(Vec3 v);
    double& at(std::size_t row, char col);
};

Vec3 add_vectors(Vec3 v1, Vec3 v2);

Vec3 subtract_vectors(Vec3 v1, Vec3 v2);

Vec2 add_vectors(Vec2 v1, Vec2 v2);

Vec2 subtract_vectors(Vec2 v1, Vec2 v2);

vector<vector<double>> rx_elementary_rotation(double angle);

vector<vector<double>> ry_elementary_rotation(double angle);

vector<vector<double>> rz_elementary_rotation(double angle);

vector<vector<double>> vector3_to_matrix(Vec3 v);

Vec3 matrix_to_vector3(vector<vector<double>> matrix);

Vec3 ftod(Vec3f v);

double angleBetweenVectors(Vec3 cp, Vec3 cv);

vector<vector<double>> multip_matrix(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2);

vector<vector<double>> multip_matrix_by_constant(vector<vector<double>> matrix, double constant);

#endif



