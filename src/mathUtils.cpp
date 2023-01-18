#include "mathUtils.h"

double& matrix4::at(size_t row, char col){
    return data[row][(col=='w' ? 3 : col-'x')];
}

double& matrix3::at(size_t row, char col){
    return data[row][col-'x'];
}

triangle2::triangle2(point2 a, point2 b, point2 c){
    this->a=a;
    this->b=b;
    this->c=c;
}

triangle2::triangle2(){
    a=point2();
    b=point2();
    c=point2();
}

line2::line2(point2 a, point2 b){
    this->a=a;
    this->b=b;
}

line2::line2(){
    a=point2();
    b=point2();
}

point2::point2(double x, double y){
    this->x=x;
    this->y=y;
}

point2::point2(){
    x=0;
    y=0;
}


