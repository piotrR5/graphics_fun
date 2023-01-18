#include <vector>
#include <cmath>
#include <iostream>

#ifndef MATHUTILS
#define MATHUTILS

/*
    punkt 3d
    wektor 3d
    rotacja 3d
    matryca 4x4

    [x,x,x,x]
    [x,x,x,x]
    [x,x,x,x]
    [x,x,x,x]

    linia 3d
    trojkat 3d
*/

struct color_RGBA{
    uint8_t r=0, g=0, b=0, a=255;
};

struct point3{
    double x=0,y=0,z=0;
    color_RGBA color;
};

struct vec3{
    double x=0, y=0, z=0;
};

struct rot3{
    double x=0, y=0, z=0;
};

class matrix4{
    double data[4][4];
    /*
      x y z w
    0 . . . .
    1 . . . .
    2 . . . .
    3 . . . .
    
    */
    double& at(std::size_t row, char col);

    /*
        TODO: dot product, matrix multiplication, matrix reversal 
    */
};

struct line3{
    point3 a,b;
};

struct triangle3{
    point3 a,b,c;
};



struct point2{
    double x=0,y=0;
    color_RGBA color;
    point2(double x, double y);
    point2();
};

struct vec2{
    double x=0, y=0;
};

struct rot2{
    double x=0, y=0;
};

class matrix3{
    double data[3][3];
    /*
      x y z 
    0 . . .
    1 . . .
    2 . . .
    
    */
    double& at(std::size_t row, char col);

    /*
        TODO: dot product, matrix multiplication, matrix reversal 
    */
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



#endif



