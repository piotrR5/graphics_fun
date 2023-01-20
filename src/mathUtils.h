#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

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
    uint8_t r, g, b, a;
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
    /*
        TODO: matrix multiplication, matrix reversal(inverse)
    */

    vector<vector<double>> data;

    /*
      x y z w
    0 . . . .
    1 . . . .
    2 . . . .
    3 . . . .
    
    */
    public:
    
    matrix4(){
        vector<double> data_row(4, 0);
        for(int i=0; i<4; i++) data.push_back(data_row);
    }

    double& at(size_t row, char col);

    vector<vector<double>> multip_matrix(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2)

    vector<vector<double>> inverse_matrix(vector<vector<double>> matrix)
    
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
};

struct triangle2{
    point2 a,b,c;
};







