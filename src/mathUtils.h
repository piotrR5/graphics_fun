#include <vector>
#include <cmath>
#include <iostream>

#ifndef MATHUTILS
#define MATHUTILS
using namespace std;

struct color_RGBA{
    uint8_t r=0, g=0, b=0, a=255;
};


struct vec4{
    double x=0, y=0, z=0, w=0;
    void add(vec4 v);
};

struct vec3{
    double x=0, y=0, z=0;
    void add(vec3 v);
};

struct vec2{
    double x=0, y=0;
    void add(vec2 v);
};

struct point3{
    double x=0,y=0,z=0;
    color_RGBA color;

    void add(vec3 v);

    vec3 makeVec3();

    point3(double x, double y, double z);
    point3();
};

struct line3{
    point3 a,b;
    line3();
    line3(point3 a, point3 b);
};

struct triangle3{
    point3 a,b,c;
    triangle3();
    triangle3(point3 a, point3 b, point3 c);
};

class matrix4{
    vector<vector<double>> data;

    public:
    
    matrix4(){
        vector<double> data_row(4, 0);
        for(int i=0; i<4; i++) data.push_back(data_row);
    }

    double& at(size_t row, char col);

    vector<vector<double>> multip_matrix(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2);

    vector<vector<double>> inverse_matrix(vector<vector<double>> matrix);
};



struct point2{
    double x=0,y=0;
    color_RGBA color;

    void add(vec2 v);

    vec2 makeVec2();

    point2(double x, double y);
    point2();
};

struct line2{
    point2 a,b;
    line2();
    line2(point2 a, point2 b);
};

struct triangle2{
    point2 a,b,c;
    triangle2();
    triangle2(point2 a, point2 b, point2 c);
};

class matrix3{
    double data[3][3];
    double& at(std::size_t row, char col);
};











#endif



