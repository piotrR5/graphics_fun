#include <vector>
#include <cmath>
#include <iostream>

#ifndef MATHUTILS
#define MATHUTILS
using namespace std;

/*
    this file contains basic implementation of mathematical and utility entities on which other parts of the project depend on
*/

struct Color_RGBA{
    uint8_t r=0, g=0, b=0, a=255;
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

class Matrix4{
    vector<vector<double>> data;

    public:
    
    Matrix4(){
        vector<double> data_row(4, 0);
        for(int i=0; i<4; i++) data.push_back(data_row);
    }

    double& at(size_t row, char col);

    vector<vector<double>> multip_matrix(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2);

    vector<vector<double>> inverse_matrix(vector<vector<double>> matrix);
};



struct Point2{
    double x=0,y=0;
    Color_RGBA color;

    void add(Vec2 v);

    Vec2 makeVec2();

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
    double data[3][3];
    double& at(std::size_t row, char col);
};











#endif



